//
//  RevisedData.swift
//  UDP
//
//  Created by Lorenzo Hernandez III on 11/30/17.
//  Copyright © 2017 Manuel Gonzalez. All rights reserved.
//

import Foundation

extension Data{
    mutating func extract(length: Int) -> Data?{
        //if no data, return
        guard self.count > 0 else{
            return nil
        }
        var range : Range<Int>
        //if data less than sending size, return
        if(self.count < length){
            range = Range(0..<self.count)
        }else{
            //cut a piece of data out and send it
            let length = length
            range = Range(0..<length)
        }
        
        let subData = self.subdata(in: range)
        self.removeSubrange(range)
        return subData
    }
}

