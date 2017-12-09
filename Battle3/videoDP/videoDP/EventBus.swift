//
//  EventBus.swift
//  videoDP
//
//  Created by Lorenzo Hernandez III on 12/7/17.
//  Copyright © 2017 Lorenzo Hernandez III. All rights reserved.
//

import Foundation
import UIKit

protocol NetworkDelegate : class {
    func notifyNetState(networkState: ConnectedState)
}
protocol FrameExtractorDelegate : class{
    func capture(image: UIImage)
}
protocol DiscoverDevicesDelegate : class{
    func connectedDevicesChanged(discoverer: DiscoverDevices, deviceList: [String])
    func startReceiving()
}
protocol StringSendDelegate : class{
    func giveString(str: String)
}
protocol AudioSendDelegate : class{
    func giveAudio()
}
protocol VideoSendDelegate : class{
    func giveFrameData(frameData: Data, last: Bool)
}
protocol ConnectedStateDelegate : class{
    func giveState(networkState: ConnectedState)
}

class EventBus {
    static let shared = EventBus()
    
    // communicate peers to everyone
    let discover = DiscoverDevices()
    
    //delegate
    weak var networkDelegate : NetworkDelegate?
    weak var frameExtractorDelegate : FrameExtractorDelegate?
    weak var discoverDevicesDelegate : DiscoverDevicesDelegate?
    weak var stringSendDelegate : StringSendDelegate?
    weak var audioSendDelegate : AudioSendDelegate?
    weak var videoSendDelegate : VideoSendDelegate?
}
