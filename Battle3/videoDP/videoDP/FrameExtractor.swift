//
//  FrameExtractor.swift
//  UDP
//
//  Created by Lorenzo Hernandez III on 12/4/17.
//  Copyright © 2017 Manuel Gonzalez. All rights reserved.
//

import AVFoundation
import UIKit


class FrameExtractor: NSObject{
    
    //bus
    let bus = EventBus.shared
    var netState = ConnectedState.noPeers
    
    //camera session
    private let capture = AVCaptureSession()
    
    //Queue
    private let queue = DispatchQueue(label: "camera")
    
    //permission to use camera
    private var permission = false
    
    //session parameters
    private let position = AVCaptureDevice.Position.front
    private let quality = AVCaptureSession.Preset.medium
    
    //context for buffer to image conversion
    private let context = CIContext()
    
    //delegate
    weak var delegate: FrameExtractorDelegate?
    
    //test
    var test = true
    
    
    override init(){
        super.init()
        checkPermission()
        
        queue.async { [unowned self] in
            self.configureSession()
            self.capture.startRunning()
        }
        
        //set up event bus delegate
        self.bus.networkDelegate = self
    }
    
    //set up camera session
    private func configureSession(){
        guard permission else { return }
        //set up quality and devices
        capture.sessionPreset = quality
        guard let captureDevice = getCaptureDevice() else { return }
        guard let captureDeviceInput = try? AVCaptureDeviceInput(device: captureDevice) else { return }
        guard capture.canAddInput(captureDeviceInput) else { return }
        capture.addInput(captureDeviceInput)
        
        //set up output for captureOutput
        let output = AVCaptureVideoDataOutput()
        output.setSampleBufferDelegate(self, queue: DispatchQueue(label: "sample buffer"))
        guard capture.canAddOutput(output) else { return }
        capture.addOutput(output)
        
        //set up orientation
        guard let connect = output.connection(with: .video) else { return }
        guard connect.isVideoOrientationSupported else { return }
        guard connect.isVideoMirroringSupported else { return }
        connect.videoOrientation = .portrait
        connect.isVideoMirrored = position == .front
    }
    
    //help config by grabbing the correct device
    private func getCaptureDevice() -> AVCaptureDevice?{
        return AVCaptureDevice.devices().filter {
            ($0 as AnyObject).hasMediaType(AVMediaType.video) &&
                ($0 as AnyObject).position == position
            }.first
    }
    
    //permission check
    func checkPermission(){
        switch AVCaptureDevice.authorizationStatus(for: AVMediaType.video){
        case .authorized:
            permission = true
            break
        case .notDetermined:
            queue.suspend()
            AVCaptureDevice.requestAccess(for: .video, completionHandler: { [unowned self] granted in
                self.permission = granted
                self.queue.resume()
            })
            break
        default:
            permission = false
            break
        }
    }
    
    //get image
    private func imageFromSampleBuffer(buffer: CMSampleBuffer) -> UIImage?{
        guard let imageBuffer = CMSampleBufferGetImageBuffer(buffer) else { return nil }
        let ci = CIImage(cvPixelBuffer: imageBuffer)
        guard let cg = context.createCGImage(ci, from: ci.extent) else { return nil }
        return UIImage(cgImage: cg)
    }
}
extension FrameExtractor : AVCaptureVideoDataOutputSampleBufferDelegate{
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        
//        if test { return }
        
        
        //buffer -> image
        guard let image = self.imageFromSampleBuffer(buffer: sampleBuffer) else { return }
        
        //queue it up
        DispatchQueue.main.async { [unowned self] in
            self.test = true
            self.delegate?.capture(image: image)
        }
    }
}
extension FrameExtractor : NetworkDelegate{
    func notifyNetState(networkState: ConnectedState) {
        print(networkState)
        self.netState = networkState
        test = false
    }
}
