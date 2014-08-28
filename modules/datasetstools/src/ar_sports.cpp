/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2014, Itseez Inc, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Itseez Inc or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include <opencv2/util.h>
#include <opencv2/ar_sports.h>

#include <cstdio>
#include <cstdlib> // atoi

#include <fstream>

using namespace std;

void loadDatasetPart(string &fileName, vector<element> &dataset)
{
    ifstream infile(fileName.c_str());
    string videoUrl, labels;
    while (infile >> videoUrl >> labels)
    {
        element curr;
        curr.videoUrl = videoUrl;

        vector<string> elems;
        split(labels, elems, ',');
        for (vector<string>::iterator it=elems.begin(); it!=elems.end(); ++it)
        {
            curr.labels.push_back(atoi((*it).c_str()));
        }

        dataset.push_back(curr);
    }
}

ar_sports::ar_sports(string &path)
{
    loadDataset(path);
}

void ar_sports::load(string &path, unsigned int number)
{
    loadDataset(path);
}

void ar_sports::loadDataset(string &path)
{
    string trainPath(path + "original/train_partition.txt");
    string testPath(path + "original/test_partition.txt");

    // loading train video urls & labels
    loadDatasetPart(trainPath, train);

    // loading test video urls & labels
    loadDatasetPart(testPath, test);
}
