//
//  allpass.h
//  spatialReverb - All
//
//  Created by Anthony Hong on 2023-12-14.
//
#pragma once

#include <stdlib.h>
#include <stdio.h>

#define NUM_DELAY_LINES 4
#define CHANNELS 2

struct apf {
    float fbGain;
    unsigned short delay;
    unsigned short ptr;
    float *delayBufOut;
    float *delayBufIn;
};

typedef apf **ALL_PASS_INFO;

ALL_PASS_INFO initAPF();

float applyApfSingle(struct apf *filter, float data);

void applyApfAll(ALL_PASS_INFO filter, float *data, int nSamples, int ch, float mix);

void freeAPF(ALL_PASS_INFO filter);
