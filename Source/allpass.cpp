//
//  allpass.c
//  spatialReverb
//
//  Created by Anthony Hong on 2023-12-14.
//
//
#include "allpass.h"

ALL_PASS_INFO initAPF() {
    ALL_PASS_INFO res = (ALL_PASS_INFO)malloc(sizeof(struct apf *));
    if (res == NULL) {
        printf("entire APF allocation failed\n");
        exit(-1);
    }
    float gains[NUM_DELAY_LINES] = {0.7, 0.45, 0.8, 0.6};
    unsigned short delays[NUM_DELAY_LINES] = {1207, 902, 689, 758};
    for (int ch = 0; ch < CHANNELS; ch++) {
        for (int n = 0; n < NUM_DELAY_LINES; n++) {
            int fInd = ch*NUM_DELAY_LINES+n;
            res[fInd] = (struct apf *)malloc(sizeof(struct apf));
            if (res == NULL) {
                printf("single APF allocation failed\n");
                exit(-1);
            }
            struct apf *f = res[fInd];
            f->delayBufIn = (float *)calloc(delays[n], sizeof(float));
            if (f->delayBufIn == NULL) {
                printf("in buf allocation failed\n");
                exit(-1);
            }
            f->delayBufOut = (float *)calloc(delays[n], sizeof(float));
            if (f->delayBufOut == NULL) {
                printf("out buf allocation failed\n");
                exit(-1);
            }
            f->delay = delays[n];
            f->ptr = 0;
            f->fbGain = gains[n];
        }
    }
    return res;
}

void applyApfAll(ALL_PASS_INFO filter, float *data, int nSamples, int ch, float mix) {
    /* y[n] = -g*x[n] + x[n-m] + g*y[n-m] */
    struct apf *ap= filter[ch];
    for (int s = 0; s < nSamples; s++) {
        float input = data[s];
        float res = -ap->fbGain*input+ap->delayBufIn[ap->ptr]+ap->fbGain*ap->delayBufOut[ap->ptr];
        ap->delayBufIn[ap->ptr] = input;
        ap->delayBufOut[ap->ptr] = res;
        ap->ptr++;
        if (ap->ptr >= ap->delay) {
            ap->ptr = 0;
        }
        data[s] = mix*res+(1.f-mix)*input;
    }
}

void freeAPF(ALL_PASS_INFO filter) {
    for (int ch = 0; ch < CHANNELS; ch++) {
        for (int n = 0; n < NUM_DELAY_LINES; n++) {
            free(filter[ch*NUM_DELAY_LINES+n]->delayBufOut);
            free(filter[ch*NUM_DELAY_LINES+n]->delayBufIn);
            free(filter[ch*NUM_DELAY_LINES+n]);
        }
    }
    free(filter);
}
