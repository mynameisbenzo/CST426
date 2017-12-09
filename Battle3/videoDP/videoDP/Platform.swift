//
//  Platform.swift
//  UDP
//
//  Created by Lorenzo Hernandez III on 11/19/17.
//  Copyright © 2017 Manuel Gonzalez. All rights reserved.
//

import Foundation
struct Platform {
    static let isSimulator: Bool = {
        var isSim = false
        #if arch(i386) || arch(x86_64)
            isSim = true
        #endif
        return isSim
    }()
}

