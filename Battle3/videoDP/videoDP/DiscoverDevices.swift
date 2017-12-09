//
//  DiscoverDevices.swift
//  UDP
//
//  Created by Manuel Gonzalez on 11/14/17.
//  Copyright © 2017 Manuel Gonzalez. All rights reserved.
//

import Foundation
import MultipeerConnectivity
import SwiftSocket

class DiscoverDevices: NSObject{
    
    let ip = IPUtility.getMyIP().ip
    
    private let ServiceType = "find-devices"
    
    private var myPeerId :MCPeerID
    private var foundIp = [String]()
    private let serviceAdverts : MCNearbyServiceAdvertiser
    private let browsePeers : MCNearbyServiceBrowser
    
    lazy var session : MCSession = {
        let session = MCSession(peer: self.myPeerId, securityIdentity: nil, encryptionPreference: .required)
        session.delegate = self
        return session
    }()
    
    var delegate : DiscoverDevicesDelegate?
    
    override init(){
        //changes our peerID to our device IP on the local network
        myPeerId = MCPeerID(displayName: "[Device Name]:\(String(describing: ip!))")
        self.serviceAdverts = MCNearbyServiceAdvertiser(peer: myPeerId, discoveryInfo: nil, serviceType: ServiceType)
        print(myPeerId)
        self.browsePeers = MCNearbyServiceBrowser(peer: myPeerId, serviceType: ServiceType)
        
        super.init()
        
        self.serviceAdverts.delegate = self
        self.serviceAdverts.startAdvertisingPeer()
        
        self.browsePeers.delegate = self
        self.browsePeers.startBrowsingForPeers()
    }
    
    deinit{
        self.serviceAdverts.stopAdvertisingPeer()
    }
}
extension DiscoverDevices: MCNearbyServiceAdvertiserDelegate{
    func advertiser(_ advertiser: MCNearbyServiceAdvertiser, didReceiveInvitationFromPeer peerID: MCPeerID, withContext context: Data?, invitationHandler: @escaping (Bool, MCSession?) -> Void) {
        print(peerID)
        //placeholder
        //will send intive to peer
        //invitationHandler(true, self.session)
    }
    
    func advertiser(_ advertiser: MCNearbyServiceAdvertiser, didNotStartAdvertisingPeer error: Error) {
        print(error)
        //placeholder
        //will return error if could not advertise
    }
}
extension DiscoverDevices: MCNearbyServiceBrowserDelegate{
    func browser(_ browser: MCNearbyServiceBrowser, lostPeer peerID: MCPeerID) {
        //lost connection to a peer
        print("Lost connection", peerID)
        let lostPeer = String(peerID.displayName.split(separator: ":")[1])
        //remove peer here or on firstViewController or both
        //can do both checks, remove from here and let the firstViewController contact the device who was "lost"
        for device in foundIp {
            if(device == String(lostPeer)){
                foundIp.filter{$0 != String(lostPeer)}
            }
        }
        self.delegate?.connectedDevicesChanged(discoverer: self, deviceList: self.foundIp)
    }
    func browser(_ browser: MCNearbyServiceBrowser, didNotStartBrowsingForPeers error: Error) {
        //could not browse for peers
        print(error)
    }
    func browser(_ browser: MCNearbyServiceBrowser, foundPeer peerID: MCPeerID, withDiscoveryInfo info: [String : String]?) {
        //found peer
        let ip = peerID.displayName.split(separator: ":")[1]
        addPeerIP(ipAddress: String(ip))
        print("Found", peerID)
        
        //We do not need to invite them so we wont have binding failed/ many operations going on
        //        browser.invitePeer(peerID, to: self.session, withContext: nil, timeout: 10)
    }
    func addPeerIP(ipAddress : String){
        if(!foundIp.contains(ipAddress)){
            foundIp.append(ipAddress)
            print("Added IP to the list")
            self.delegate?.connectedDevicesChanged(discoverer: self, deviceList: self.foundIp)
        }else{
            print("Already in list")
        }
    }
}
extension DiscoverDevices : MCSessionDelegate{
    func session(_ session: MCSession, didReceive data: Data, fromPeer peerID: MCPeerID) {
        //received data
        print(data.count)
    }
    func session(_ session: MCSession, peer peerID: MCPeerID, didChange state: MCSessionState) {
        //new peer in session
        print(peerID)
    }
    func session(_ session: MCSession, didReceive stream: InputStream, withName streamName: String, fromPeer peerID: MCPeerID) {
        //receiving stream... WHAT DOES THIS DO!?!?
        print("?")
    }
    func session(_ session: MCSession, didStartReceivingResourceWithName resourceName: String, fromPeer peerID: MCPeerID, with progress: Progress) {
        //initial handshake for resource sending
        print(resourceName)
        print(progress)
    }
    func session(_ session: MCSession, didFinishReceivingResourceWithName resourceName: String, fromPeer peerID: MCPeerID, at localURL: URL?, withError error: Error?) {
        //successfully received resource
        print(resourceName)
    }
}


