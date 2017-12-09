//
//  ViewController.swift
//  videoDP
//
//  Created by Lorenzo Hernandez III on 12/7/17.
//  Copyright © 2017 Lorenzo Hernandez III. All rights reserved.
//

import UIKit
import AVFoundation
import SwiftSocket

class ViewController: UIViewController {

    //Mark: Event Bus
    let bus = EventBus.shared
    
    //Mark: variable instances
    
    //Network Handler
    var network = NetworkHandler()
    
    // Display layer and camera functionaliity
    var displayImage : UIImage?
    var extractor : FrameExtractor!
    var displayView : UIImageView?
    var displayLayer : CALayer?
    
    // picture data
    var picData = Data()
    
    
    var lotsOfPicData = [String : Int]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        //check if simulator
        if !Platform.isSimulator{
            extractor = FrameExtractor()
            extractor.delegate = self
        }
        
        //insure NetworkHandler is up and running
        bus.discover.delegate = self
        network.checkStartServer()
        bus.videoSendDelegate = self
        
        //create imageview and add
        self.displayView = UIImageView(frame: CGRect(x: 5, y: 5, width: self.view.bounds.width/3, height: self.view.bounds.height/4))
        self.view.addSubview(displayView!)
        
        //add imageview to display layer
        self.displayLayer = CALayer{
            return self.displayView!.layer
        }
        setupDisplayLayer()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    //Mark: test functions [DELETE ME]
    func testDataSeperation(){
        
        let string = "a"
        
        var testData = string.data(using: .utf8)
        
        let string2 = "1234"
        
        let testData2 = string2.data(using: .utf8)
        
        testData?.append(testData2!)
        
        self.network.sendStringData(strData: testData!)
    }
    
    //Mark: private functions
    
    //setting up facetime-esque display layer
    private func setupDisplayLayer(){
        self.displayLayer!.backgroundColor = UIColor.blue.cgColor
        self.displayLayer!.cornerRadius = 1.0
        self.displayLayer!.shadowOpacity = 0.7
        self.displayLayer!.shadowRadius = 10.0
        self.displayLayer!.contents = displayView!
        self.displayLayer!.contentsGravity = kCAGravityResizeAspectFill
    }
}
extension ViewController : FrameExtractorDelegate{
    func capture(image: UIImage) {
        
        
        //turn this back on after vvvv
//        var data = UIImagePNGRepresentation(image)
//        repeat {
//            let segment = data!.extract(length: 1024*8)
//            print(segment!.count)
//            self.network.sendVideo(da: segment!)
//        } while(data!.count >= 1)
    }
}

extension ViewController: DiscoverDevicesDelegate{
    func startReceiving() {
        //oy
    }
    
    func connectedDevicesChanged(discoverer: DiscoverDevices, deviceList: [String]) {
        //send list of connected devices to label to create list
        OperationQueue.main.addOperation {
            self.network.clientList = [UDPClient]()
            if !deviceList.isEmpty{
                // need to make currentClient nil or something else
                self.network.currentClient = UDPClient(address: "", port: 8080)
                //client List copies deviceList
                for address in deviceList{
                    //appends all to list
                    self.network.addClient(ip: address)
                }
            } else{
                print("No one is here")
            }
        }
    }
}
extension ViewController : VideoSendDelegate{
    func giveFrameData(frameData: Data, last: Bool) {
        //get frame
        DispatchQueue.main.async {
            print("\(frameData.count)")
            
            
            //turn this back on after vvvv
//            if(last){
//
//                self.displayView?.image  = UIImage(data: self.picData)
//                self.picData.removeAll()
//            } else{
//                self.picData += frameData
//            }
        }
    }}
