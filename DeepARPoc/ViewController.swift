//
//  ViewController.swift
//  DeepARPoc
//
//  Created by Váradi Valentin on 2020. 08. 27..
//  Copyright © 2020. Váradi Valentin. All rights reserved.
//

import UIKit
import DeepAR

class ViewController: UIViewController {

    let cameraController = CameraController()
    let deepAR = DeepAR()

    override func viewDidLoad() {
        super.viewDidLoad()
        deepAR.setLicenseKey("")
        deepAR.delegate = self

        // Create camera view
        guard let renderView = deepAR.createARView(withFrame: self.view.bounds) else { return }
        view.addSubview(renderView)
        renderView.bindFrameToSuperviewBounds()

        cameraController?.deepAR = deepAR
        cameraController?.startCamera()
        deepAR.startCapture(withOutputWidth: 720,
                            outputHeight: 1280,
                            subframe: CGRect(x: 0,
                                             y: 0,
                                             width: 1,
                                             height: 1))
    }
}

extension ViewController: DeepARDelegate {
    func frameAvailable(_ sampleBuffer: CMSampleBuffer!) {
        DispatchQueue.main.async {
            if let cvImageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer) {
                let ciimage = CIImage(cvImageBuffer: cvImageBuffer)
                let context = CIContext()

                if let cgImage = context.createCGImage(ciimage, from: ciimage.extent) {
                    let image = UIImage(cgImage: cgImage)

                    let imageView = UIImageView(image: image)
                    imageView.frame = CGRect(x: 0, y: 0, width: 100, height: 100)
                    imageView.contentMode = .scaleAspectFit
                    imageView.image = image
                    imageView.backgroundColor = .white

                    self.view.addSubview(imageView)
                    self.view.bringSubviewToFront(imageView)
                    DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 2) {
                        imageView.removeFromSuperview()
                    }
                }
            }
        }
    }
}


extension UIView {
    func bindFrameToSuperviewBounds() {
        guard let superview = self.superview else {
            print("Error! `superview` was nil – call `addSubview(view: UIView)`" +
                "before calling `bindFrameToSuperviewBounds()` to fix this.")
            return
        }

        self.translatesAutoresizingMaskIntoConstraints = false
        self.topAnchor.constraint(equalTo: superview.topAnchor, constant: 0).isActive = true
        self.bottomAnchor.constraint(equalTo: superview.bottomAnchor, constant: 0).isActive = true
        self.leadingAnchor.constraint(equalTo: superview.leadingAnchor, constant: 0).isActive = true
        self.trailingAnchor.constraint(equalTo: superview.trailingAnchor, constant: 0).isActive = true
    }
}
