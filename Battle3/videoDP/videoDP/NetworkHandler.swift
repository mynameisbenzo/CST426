//
//  MainController.swift
//  SnapchatSwipeView
//
//  Created by Lorenzo Hernandez III on 11/18/17.
//  Copyright © 2017 Brendan Lee. All rights reserved.
//

import UIKit
import SwiftSocket
import AVFoundation

public enum ConnectedState{
    case peersDetected
    case noPeers
}

class NetworkHandler : NSObject{
    
    //Mark: event bus
    let bus = EventBus.shared
    
    //Mark: Instance Variables
    let ipAddr = IPUtility.getMyIP().ip
    let buffer = 1024
    var server : UDPServer!
    var currentClient: UDPClient!
    var clientList = [UDPClient]()
    var video : Data?
    
    //test
    var bytes = Data()
    
    //constructor
    override init(){
        super.init()
    }
    
    
    func checkStartServer(){
        self.server = UDPServer(address: ipAddr!, port: 8080)
        self.receiveData()
    }
    
    /*
     // MARK: - Navigation
     
     // In a storyboard-based application, you will often want to do a little preparation before navigation
     override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
     // Get the new view controller using segue.destinationViewController.
     // Pass the selected object to the new view controller.
     }
     */
    
    //Mark: Private functions
    private func change(res: String){
        bus.stringSendDelegate?.giveString(str: res)
    }
//    private func videoUpdate(fr: Data){
//        self.third?.giveFrameData(frameData: fr, last: false)
//    }
    //Mark: Public functions
    func receiveData(){
        DispatchQueue.global(qos: .background).async {
            let data = self.server.recv(1024 * 8)
            if(data.0 == nil) { return }
            if let response = data.0{
                self.bytes.append(contentsOf: response)
                if(response.count < 1024 * 8 && response.count > 0){
                    self.bus.videoSendDelegate?.giveFrameData(frameData: self.bytes, last: true)
                }else{
                    self.bus.videoSendDelegate?.giveFrameData(frameData: self.bytes, last: false)
                }
                self.bytes.removeAll()
            }
            self.receiveData()
        }
    }
    func sendStringData(strData: Data){
        if(self.clientList.count < 0){ return }
        if(strData.isEmpty){ return }
        for client in self.clientList{ //sends to all connected users
            self.currentClient = client
            print("Sending to ...", self.currentClient.address)
            self.currentClient.send(data: strData) //sends the data
            let ip = self.currentClient.address
            let port = self.currentClient.port
            self.currentClient.close()
            self.currentClient = UDPClient(address: ip, port: port)
        }
    }
    func sendStringFromTextField(tf: UITextField){
        if(self.clientList.count > 0){
            for client in self.clientList{ //sends to all connected users
                self.currentClient = client
                //Prints out who the data is being sent to
                if !((tf.text?.isEmpty)!) {
                    print("Sending to ...", self.currentClient.address)
                    self.currentClient.send(string: tf.text!) //sends the data
                    let ip = self.currentClient.address
                    let port = self.currentClient.port
                    self.currentClient.close()
                    self.currentClient = UDPClient(address: ip, port: port)
                }else{
                    print("textField is empty")
                    return
                }
            }
        }else{
            print("No Clients Available")
        }
    }
    func sendVideo(da: Data){
        if(self.clientList.count > 0){
            for client in self.clientList{ //sends to all connected users
                self.currentClient = client
                //Sends data to everyone's preview layer
                switch(self.currentClient.send(data: da)){
                case Result.success:
                    break
                case Result.failure(let error):
                    print("oh no bro: \(error)")
                    break
                }
            }
        }else{
            print("No Clients Available")
        }
    }
    func addClient(newClient: UDPClient){
        clientList.append(newClient)
        self.bus.networkDelegate?.notifyNetState(networkState: .peersDetected)

    }
    func addClient(ip: String){
        clientList.append(UDPClient(address: ip, port: 8080))
        self.bus.networkDelegate?.notifyNetState(networkState: .peersDetected)
    }
    func shutdownSC(){
        self.server.close()
        for client in clientList{
            client.close()
        }
    }
    func restartSC(){
        self.server = UDPServer(address: ipAddr!, port: 8080)
    }
    
    // give network state
    func checkNetworkState() -> ConnectedState{
        if(self.clientList.count > 0){
            return .peersDetected
        }
        return .noPeers
    }
}

