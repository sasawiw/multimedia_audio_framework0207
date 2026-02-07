/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "audio_ec_manager_unit_test.h"

using namespace testing::ext;

namespace OHOS {
namespace AudioStandard {

void AudioEcManagerUnitTest::SetUpTestCase(void) {}
void AudioEcManagerUnitTest::TearDownTestCase(void) {}

void AudioEcManagerUnitTest::SetUp(void)
{
    audioEcManager_ = &AudioEcManager::GetInstance();
}

void AudioEcManagerUnitTest::TearDown(void)
{
    audioEcManager_ = nullptr;
}

/**
 * @tc.name  : Init_001
 * @tc.number: AudioEcManagerUnitTest_Init_001
 * @tc.desc  : Test Init with both ec and micRef enabled
 */
HWTEST_F(AudioEcManagerUnitTest, Init_001, TestSize.Level2)
{
    audioEcManager_->Init(1, 1);
    EXPECT_TRUE(audioEcManager_->GetEcFeatureEnable());
    EXPECT_TRUE(audioEcManager_->GetMicRefFeatureEnable());
}

/**
 * @tc.name  : Init_002
 * @tc.number: AudioEcManagerUnitTest_Init_002
 * @tc.desc  : Test Init with both ec and micRef disabled
 */
HWTEST_F(AudioEcManagerUnitTest, Init_002, TestSize.Level2)
{
    audioEcManager_->Init(0, 0);
    EXPECT_FALSE(audioEcManager_->GetEcFeatureEnable());
    EXPECT_FALSE(audioEcManager_->GetMicRefFeatureEnable());
}

/**
 * @tc.name  : Init_003
 * @tc.number: AudioEcManagerUnitTest_Init_003
 * @tc.desc  : Test Init with ec enabled and micRef disabled
 */
HWTEST_F(AudioEcManagerUnitTest, Init_003, TestSize.Level2)
{
    audioEcManager_->Init(1, 0);
    EXPECT_TRUE(audioEcManager_->GetEcFeatureEnable());
    EXPECT_FALSE(audioEcManager_->GetMicRefFeatureEnable());
}

/**
 * @tc.name  : GetEcFeatureEnable_001
 * @tc.number: AudioEcManagerUnitTest_GetEcFeatureEnable_001
 * @tc.desc  : Test GetEcFeatureEnable returns correct value after Init
 */
HWTEST_F(AudioEcManagerUnitTest, GetEcFeatureEnable_001, TestSize.Level3)
{
    audioEcManager_->isEcFeatureEnable_ = false;
    EXPECT_FALSE(audioEcManager_->GetEcFeatureEnable());
    audioEcManager_->isEcFeatureEnable_ = true;
    EXPECT_TRUE(audioEcManager_->GetEcFeatureEnable());
}

/**
 * @tc.name  : GetMicRefFeatureEnable_001
 * @tc.number: AudioEcManagerUnitTest_GetMicRefFeatureEnable_001
 * @tc.desc  : Test GetMicRefFeatureEnable returns correct value
 */
HWTEST_F(AudioEcManagerUnitTest, GetMicRefFeatureEnable_001, TestSize.Level3)
{
    audioEcManager_->isMicRefFeatureEnable_ = false;
    EXPECT_FALSE(audioEcManager_->GetMicRefFeatureEnable());
    audioEcManager_->isMicRefFeatureEnable_ = true;
    EXPECT_TRUE(audioEcManager_->GetMicRefFeatureEnable());
}

/**
 * @tc.name  : GetSourceOpened_001
 * @tc.number: AudioEcManagerUnitTest_GetSourceOpened_001
 * @tc.desc  : Test GetSourceOpened returns initial value
 */
HWTEST_F(AudioEcManagerUnitTest, GetSourceOpened_001, TestSize.Level3)
{
    audioEcManager_->normalSourceOpened_ = SOURCE_TYPE_INVALID;
    EXPECT_EQ(audioEcManager_->GetSourceOpened(), SOURCE_TYPE_INVALID);
}

/**
 * @tc.name  : SetOpenedNormalSource_001
 * @tc.number: AudioEcManagerUnitTest_SetOpenedNormalSource_001
 * @tc.desc  : Test SetOpenedNormalSource sets the correct source type
 */
HWTEST_F(AudioEcManagerUnitTest, SetOpenedNormalSource_001, TestSize.Level2)
{
    audioEcManager_->SetOpenedNormalSource(SOURCE_TYPE_MIC);
    EXPECT_EQ(audioEcManager_->GetSourceOpened(), SOURCE_TYPE_MIC);

    audioEcManager_->SetOpenedNormalSource(SOURCE_TYPE_VOICE_COMMUNICATION);
    EXPECT_EQ(audioEcManager_->GetSourceOpened(), SOURCE_TYPE_VOICE_COMMUNICATION);

    audioEcManager_->SetOpenedNormalSource(SOURCE_TYPE_INVALID);
    EXPECT_EQ(audioEcManager_->GetSourceOpened(), SOURCE_TYPE_INVALID);
}

/**
 * @tc.name  : SetOpenedNormalSourceSessionId_001
 * @tc.number: AudioEcManagerUnitTest_SetOpenedNormalSourceSessionId_001
 * @tc.desc  : Test SetOpenedNormalSourceSessionId and GetOpenedNormalSourceSessionId
 */
HWTEST_F(AudioEcManagerUnitTest, SetOpenedNormalSourceSessionId_001, TestSize.Level2)
{
    uint64_t sessionId = 12345;
    audioEcManager_->SetOpenedNormalSourceSessionId(sessionId);
    EXPECT_EQ(audioEcManager_->GetOpenedNormalSourceSessionId(), sessionId);

    audioEcManager_->SetOpenedNormalSourceSessionId(0);
    EXPECT_EQ(audioEcManager_->GetOpenedNormalSourceSessionId(), 0);
}

/**
 * @tc.name  : SetDpSinkModuleInfo_001
 * @tc.number: AudioEcManagerUnitTest_SetDpSinkModuleInfo_001
 * @tc.desc  : Test SetDpSinkModuleInfo saves module info correctly
 */
HWTEST_F(AudioEcManagerUnitTest, SetDpSinkModuleInfo_001, TestSize.Level3)
{
    AudioModuleInfo moduleInfo;
    moduleInfo.rate = "48000";
    moduleInfo.channels = "2";
    moduleInfo.format = "s16le";
    audioEcManager_->SetDpSinkModuleInfo(moduleInfo);
    EXPECT_EQ(audioEcManager_->dpSinkModuleInfo_.rate, "48000");
    EXPECT_EQ(audioEcManager_->dpSinkModuleInfo_.channels, "2");
    EXPECT_EQ(audioEcManager_->dpSinkModuleInfo_.format, "s16le");
}

/**
 * @tc.name  : SetPrimaryMicModuleInfo_001
 * @tc.number: AudioEcManagerUnitTest_SetPrimaryMicModuleInfo_001
 * @tc.desc  : Test SetPrimaryMicModuleInfo saves module info correctly
 */
HWTEST_F(AudioEcManagerUnitTest, SetPrimaryMicModuleInfo_001, TestSize.Level3)
{
    AudioModuleInfo moduleInfo;
    moduleInfo.rate = "16000";
    moduleInfo.channels = "1";
    moduleInfo.format = "s16le";
    audioEcManager_->SetPrimaryMicModuleInfo(moduleInfo);
    EXPECT_EQ(audioEcManager_->primaryMicModuleInfo_.rate, "16000");
    EXPECT_EQ(audioEcManager_->primaryMicModuleInfo_.channels, "1");
    EXPECT_EQ(audioEcManager_->primaryMicModuleInfo_.format, "s16le");
}

/**
 * @tc.name  : ClearModuleInfoForEc_001
 * @tc.number: AudioEcManagerUnitTest_ClearModuleInfoForEc_001
 * @tc.desc  : Test ClearModuleInfoForEc clears all ec fields
 */
HWTEST_F(AudioEcManagerUnitTest, ClearModuleInfoForEc_001, TestSize.Level2)
{
    AudioModuleInfo moduleInfo;
    moduleInfo.ecType = "1";
    moduleInfo.ecAdapter = "primary";
    moduleInfo.ecSamplingRate = "48000";
    moduleInfo.ecFormat = "s16le";
    moduleInfo.ecChannels = "2";
    audioEcManager_->ClearModuleInfoForEc(moduleInfo);
    EXPECT_EQ(moduleInfo.ecType, "");
    EXPECT_EQ(moduleInfo.ecAdapter, "");
    EXPECT_EQ(moduleInfo.ecSamplingRate, "");
    EXPECT_EQ(moduleInfo.ecFormat, "");
    EXPECT_EQ(moduleInfo.ecChannels, "");
}

/**
 * @tc.name  : ClearModuleInfoForMicRef_001
 * @tc.number: AudioEcManagerUnitTest_ClearModuleInfoForMicRef_001
 * @tc.desc  : Test ClearModuleInfoForMicRef clears all mic ref fields
 */
HWTEST_F(AudioEcManagerUnitTest, ClearModuleInfoForMicRef_001, TestSize.Level2)
{
    AudioModuleInfo moduleInfo;
    moduleInfo.openMicRef = "1";
    moduleInfo.micRefRate = "48000";
    moduleInfo.micRefFormat = "s16le";
    moduleInfo.micRefChannels = "4";
    audioEcManager_->ClearModuleInfoForMicRef(moduleInfo);
    EXPECT_EQ(moduleInfo.openMicRef, "0");
    EXPECT_EQ(moduleInfo.micRefRate, "");
    EXPECT_EQ(moduleInfo.micRefFormat, "");
    EXPECT_EQ(moduleInfo.micRefChannels, "");
}

/**
 * @tc.name  : GetAudioEcInfo_001
 * @tc.number: AudioEcManagerUnitTest_GetAudioEcInfo_001
 * @tc.desc  : Test GetAudioEcInfo returns current ec info
 */
HWTEST_F(AudioEcManagerUnitTest, GetAudioEcInfo_001, TestSize.Level2)
{
    AudioEcInfo ecInfo = audioEcManager_->GetAudioEcInfo();
    EXPECT_NE(audioEcManager_, nullptr);
}

/**
 * @tc.name  : ResetAudioEcInfo_001
 * @tc.number: AudioEcManagerUnitTest_ResetAudioEcInfo_001
 * @tc.desc  : Test ResetAudioEcInfo resets device types to DEVICE_TYPE_NONE
 */
HWTEST_F(AudioEcManagerUnitTest, ResetAudioEcInfo_001, TestSize.Level2)
{
    audioEcManager_->ResetAudioEcInfo();
    AudioEcInfo ecInfo = audioEcManager_->GetAudioEcInfo();
    EXPECT_EQ(ecInfo.inputDevice.deviceType_, DEVICE_TYPE_NONE);
    EXPECT_EQ(ecInfo.outputDevice.deviceType_, DEVICE_TYPE_NONE);
}

/**
 * @tc.name  : GetTargetSourceTypeAndMatchingFlag_001
 * @tc.number: AudioEcManagerUnitTest_GetTargetSourceTypeAndMatchingFlag_001
 * @tc.desc  : Test GetTargetSourceTypeAndMatchingFlag for SOURCE_TYPE_VOICE_RECOGNITION
 */
HWTEST_F(AudioEcManagerUnitTest, GetTargetSourceTypeAndMatchingFlag_001, TestSize.Level2)
{
    SourceType targetSource = SOURCE_TYPE_INVALID;
    bool useMatchingPropInfo = false;
    audioEcManager_->GetTargetSourceTypeAndMatchingFlag(SOURCE_TYPE_VOICE_RECOGNITION,
        targetSource, useMatchingPropInfo);
    EXPECT_EQ(targetSource, SOURCE_TYPE_VOICE_RECOGNITION);
    EXPECT_TRUE(useMatchingPropInfo);
}

/**
 * @tc.name  : GetTargetSourceTypeAndMatchingFlag_002
 * @tc.number: AudioEcManagerUnitTest_GetTargetSourceTypeAndMatchingFlag_002
 * @tc.desc  : Test GetTargetSourceTypeAndMatchingFlag for SOURCE_TYPE_VOICE_COMMUNICATION
 */
HWTEST_F(AudioEcManagerUnitTest, GetTargetSourceTypeAndMatchingFlag_002, TestSize.Level2)
{
    SourceType targetSource = SOURCE_TYPE_INVALID;
    bool useMatchingPropInfo = false;
    audioEcManager_->isEcFeatureEnable_ = false;
    audioEcManager_->GetTargetSourceTypeAndMatchingFlag(SOURCE_TYPE_VOICE_COMMUNICATION,
        targetSource, useMatchingPropInfo);
    EXPECT_EQ(targetSource, SOURCE_TYPE_VOICE_COMMUNICATION);
    EXPECT_TRUE(useMatchingPropInfo);
}

/**
 * @tc.name  : GetTargetSourceTypeAndMatchingFlag_003
 * @tc.number: AudioEcManagerUnitTest_GetTargetSourceTypeAndMatchingFlag_003
 * @tc.desc  : Test GetTargetSourceTypeAndMatchingFlag for SOURCE_TYPE_VOICE_COMMUNICATION with ec enabled
 */
HWTEST_F(AudioEcManagerUnitTest, GetTargetSourceTypeAndMatchingFlag_003, TestSize.Level2)
{
    SourceType targetSource = SOURCE_TYPE_INVALID;
    bool useMatchingPropInfo = true;
    audioEcManager_->isEcFeatureEnable_ = true;
    audioEcManager_->GetTargetSourceTypeAndMatchingFlag(SOURCE_TYPE_VOICE_COMMUNICATION,
        targetSource, useMatchingPropInfo);
    EXPECT_EQ(targetSource, SOURCE_TYPE_VOICE_COMMUNICATION);
    EXPECT_FALSE(useMatchingPropInfo);
}

/**
 * @tc.name  : GetTargetSourceTypeAndMatchingFlag_004
 * @tc.number: AudioEcManagerUnitTest_GetTargetSourceTypeAndMatchingFlag_004
 * @tc.desc  : Test GetTargetSourceTypeAndMatchingFlag for SOURCE_TYPE_VOICE_TRANSCRIPTION
 */
HWTEST_F(AudioEcManagerUnitTest, GetTargetSourceTypeAndMatchingFlag_004, TestSize.Level2)
{
    SourceType targetSource = SOURCE_TYPE_INVALID;
    bool useMatchingPropInfo = false;
    audioEcManager_->isEcFeatureEnable_ = false;
    audioEcManager_->GetTargetSourceTypeAndMatchingFlag(SOURCE_TYPE_VOICE_TRANSCRIPTION,
        targetSource, useMatchingPropInfo);
    EXPECT_EQ(targetSource, SOURCE_TYPE_VOICE_COMMUNICATION);
    EXPECT_TRUE(useMatchingPropInfo);
}

/**
 * @tc.name  : GetTargetSourceTypeAndMatchingFlag_005
 * @tc.number: AudioEcManagerUnitTest_GetTargetSourceTypeAndMatchingFlag_005
 * @tc.desc  : Test GetTargetSourceTypeAndMatchingFlag for SOURCE_TYPE_VOICE_CALL
 */
HWTEST_F(AudioEcManagerUnitTest, GetTargetSourceTypeAndMatchingFlag_005, TestSize.Level2)
{
    SourceType targetSource = SOURCE_TYPE_INVALID;
    bool useMatchingPropInfo = true;
    audioEcManager_->GetTargetSourceTypeAndMatchingFlag(SOURCE_TYPE_VOICE_CALL, targetSource, useMatchingPropInfo);
    EXPECT_EQ(targetSource, SOURCE_TYPE_VOICE_CALL);
}

/**
 * @tc.name  : GetTargetSourceTypeAndMatchingFlag_006
 * @tc.number: AudioEcManagerUnitTest_GetTargetSourceTypeAndMatchingFlag_006
 * @tc.desc  : Test GetTargetSourceTypeAndMatchingFlag for SOURCE_TYPE_UNPROCESSED
 */
HWTEST_F(AudioEcManagerUnitTest, GetTargetSourceTypeAndMatchingFlag_006, TestSize.Level2)
{
    SourceType targetSource = SOURCE_TYPE_INVALID;
    bool useMatchingPropInfo = false;
    audioEcManager_->GetTargetSourceTypeAndMatchingFlag(SOURCE_TYPE_UNPROCESSED, targetSource, useMatchingPropInfo);
    EXPECT_EQ(targetSource, SOURCE_TYPE_UNPROCESSED);
    EXPECT_TRUE(useMatchingPropInfo);
}

/**
 * @tc.name  : GetTargetSourceTypeAndMatchingFlag_007
 * @tc.number: AudioEcManagerUnitTest_GetTargetSourceTypeAndMatchingFlag_007
 * @tc.desc  : Test GetTargetSourceTypeAndMatchingFlag for SOURCE_TYPE_LIVE
 */
HWTEST_F(AudioEcManagerUnitTest, GetTargetSourceTypeAndMatchingFlag_007, TestSize.Level2)
{
    SourceType targetSource = SOURCE_TYPE_INVALID;
    bool useMatchingPropInfo = false;
    audioEcManager_->GetTargetSourceTypeAndMatchingFlag(SOURCE_TYPE_LIVE, targetSource, useMatchingPropInfo);
    EXPECT_EQ(targetSource, SOURCE_TYPE_LIVE);
}

/**
 * @tc.name  : GetTargetSourceTypeAndMatchingFlag_008
 * @tc.number: AudioEcManagerUnitTest_GetTargetSourceTypeAndMatchingFlag_008
 * @tc.desc  : Test GetTargetSourceTypeAndMatchingFlag for default case (SOURCE_TYPE_CAMCORDER)
 */
HWTEST_F(AudioEcManagerUnitTest, GetTargetSourceTypeAndMatchingFlag_008, TestSize.Level3)
{
    SourceType targetSource = SOURCE_TYPE_INVALID;
    bool useMatchingPropInfo = false;
    audioEcManager_->GetTargetSourceTypeAndMatchingFlag(SOURCE_TYPE_CAMCORDER, targetSource, useMatchingPropInfo);
    EXPECT_EQ(targetSource, SOURCE_TYPE_MIC);
}

/**
 * @tc.name  : UpdateStreamEcInfo_001
 * @tc.number: AudioEcManagerUnitTest_UpdateStreamEcInfo_001
 * @tc.desc  : Test UpdateStreamEcInfo clears ec data for non-VOIP source types
 */
HWTEST_F(AudioEcManagerUnitTest, UpdateStreamEcInfo_001, TestSize.Level2)
{
    AudioModuleInfo moduleInfo;
    moduleInfo.ecType = "1";
    moduleInfo.ecAdapter = "primary";
    audioEcManager_->UpdateStreamEcInfo(moduleInfo, SOURCE_TYPE_MIC);
    EXPECT_EQ(moduleInfo.ecType, "");
    EXPECT_EQ(moduleInfo.ecAdapter, "");
}

/**
 * @tc.name  : UpdateStreamMicRefInfo_001
 * @tc.number: AudioEcManagerUnitTest_UpdateStreamMicRefInfo_001
 * @tc.desc  : Test UpdateStreamMicRefInfo clears mic ref for non-VOIP non-MIC source types
 */
HWTEST_F(AudioEcManagerUnitTest, UpdateStreamMicRefInfo_001, TestSize.Level2)
{
    AudioModuleInfo moduleInfo;
    moduleInfo.openMicRef = "1";
    audioEcManager_->UpdateStreamMicRefInfo(moduleInfo, SOURCE_TYPE_CAMCORDER);
    EXPECT_EQ(moduleInfo.openMicRef, "0");
    EXPECT_EQ(moduleInfo.micRefRate, "");
}

/**
 * @tc.name  : UpdateModuleInfoForPrimary_001
 * @tc.number: AudioEcManagerUnitTest_UpdateModuleInfoForPrimary_001
 * @tc.desc  : Test UpdateModuleInfoForPrimary with non-primary adapter name does nothing
 */
HWTEST_F(AudioEcManagerUnitTest, UpdateModuleInfoForPrimary_001, TestSize.Level3)
{
    AudioModuleInfo moduleInfo;
    moduleInfo.adapterName = "usb";
    moduleInfo.channels = "2";
    PipeStreamPropInfo targetInfo;
    targetInfo.channels_ = 4;
    audioEcManager_->UpdateModuleInfoForPrimary(moduleInfo, targetInfo);
    EXPECT_EQ(moduleInfo.channels, "2");
}

/**
 * @tc.name  : UpdateModuleInfoForPrimary_002
 * @tc.number: AudioEcManagerUnitTest_UpdateModuleInfoForPrimary_002
 * @tc.desc  : Test UpdateModuleInfoForPrimary with primary adapter name updates info
 */
HWTEST_F(AudioEcManagerUnitTest, UpdateModuleInfoForPrimary_002, TestSize.Level2)
{
    AudioModuleInfo moduleInfo;
    moduleInfo.adapterName = "primary";
    PipeStreamPropInfo targetInfo;
    targetInfo.channels_ = 4;
    targetInfo.sampleRate_ = 48000;
    targetInfo.bufferSize_ = 1920;
    targetInfo.format_ = SAMPLE_S16LE;
    targetInfo.channelLayout_ = CH_LAYOUT_QUAD;
    audioEcManager_->UpdateModuleInfoForPrimary(moduleInfo, targetInfo);
    EXPECT_EQ(moduleInfo.channels, "4");
    EXPECT_EQ(moduleInfo.rate, "48000");
    EXPECT_EQ(moduleInfo.bufferSize, "1920");
}

/**
 * @tc.name  : UpdateAudioEcInfo_001
 * @tc.number: AudioEcManagerUnitTest_UpdateAudioEcInfo_001
 * @tc.desc  : Test UpdateAudioEcInfo when ec feature is disabled
 */
HWTEST_F(AudioEcManagerUnitTest, UpdateAudioEcInfo_001, TestSize.Level3)
{
    audioEcManager_->isEcFeatureEnable_ = false;
    AudioDeviceDescriptor inputDevice;
    inputDevice.deviceType_ = DEVICE_TYPE_MIC;
    AudioDeviceDescriptor outputDevice;
    outputDevice.deviceType_ = DEVICE_TYPE_SPEAKER;
    audioEcManager_->UpdateAudioEcInfo(inputDevice, outputDevice);
    EXPECT_NE(audioEcManager_, nullptr);
}

/**
 * @tc.name  : UpdateModuleInfoForEc_001
 * @tc.number: AudioEcManagerUnitTest_UpdateModuleInfoForEc_001
 * @tc.desc  : Test UpdateModuleInfoForEc writes ec info to module info
 */
HWTEST_F(AudioEcManagerUnitTest, UpdateModuleInfoForEc_001, TestSize.Level2)
{
    audioEcManager_->audioEcInfo_.ecType = EC_TYPE_SAME_ADAPTER;
    audioEcManager_->audioEcInfo_.samplingRate = "48000";
    audioEcManager_->audioEcInfo_.format = "s16le";
    audioEcManager_->audioEcInfo_.channels = "2";
    audioEcManager_->audioEcInfo_.ecOutputAdapter = "primary";

    AudioModuleInfo moduleInfo;
    audioEcManager_->UpdateModuleInfoForEc(moduleInfo);
    EXPECT_EQ(moduleInfo.ecType, std::to_string(EC_TYPE_SAME_ADAPTER));
    EXPECT_EQ(moduleInfo.ecAdapter, "primary");
    EXPECT_EQ(moduleInfo.ecSamplingRate, "48000");
    EXPECT_EQ(moduleInfo.ecFormat, "s16le");
    EXPECT_EQ(moduleInfo.ecChannels, "2");
}

/**
 * @tc.name  : UpdateStreamEcAndMicRefInfo_001
 * @tc.number: AudioEcManagerUnitTest_UpdateStreamEcAndMicRefInfo_001
 * @tc.desc  : Test UpdateStreamEcAndMicRefInfo for non-voip source clears both ec and micref
 */
HWTEST_F(AudioEcManagerUnitTest, UpdateStreamEcAndMicRefInfo_001, TestSize.Level2)
{
    AudioModuleInfo moduleInfo;
    moduleInfo.ecType = "1";
    moduleInfo.openMicRef = "1";
    audioEcManager_->UpdateStreamEcAndMicRefInfo(moduleInfo, SOURCE_TYPE_CAMCORDER);
    EXPECT_EQ(moduleInfo.ecType, "");
    EXPECT_EQ(moduleInfo.openMicRef, "0");
}

/**
 * @tc.name  : IsValidSourcePipe_001
 * @tc.number: AudioEcManagerUnitTest_IsValidSourcePipe_001
 * @tc.desc  : Test IsValidSourcePipe with nullptr
 */
HWTEST_F(AudioEcManagerUnitTest, IsValidSourcePipe_001, TestSize.Level3)
{
    std::shared_ptr<AudioPipeInfo> pipeInfo = nullptr;
    EXPECT_FALSE(audioEcManager_->IsValidSourcePipe(pipeInfo, false));
}

/**
 * @tc.name  : IsValidSourcePipe_002
 * @tc.number: AudioEcManagerUnitTest_IsValidSourcePipe_002
 * @tc.desc  : Test IsValidSourcePipe with valid common pipe name
 */
HWTEST_F(AudioEcManagerUnitTest, IsValidSourcePipe_002, TestSize.Level2)
{
    std::shared_ptr<AudioPipeInfo> pipeInfo = std::make_shared<AudioPipeInfo>();
    pipeInfo->name_ = "primary_input";
    EXPECT_TRUE(audioEcManager_->IsValidSourcePipe(pipeInfo, false));
}

/**
 * @tc.name  : IsValidSourcePipe_003
 * @tc.number: AudioEcManagerUnitTest_IsValidSourcePipe_003
 * @tc.desc  : Test IsValidSourcePipe with invalid pipe name
 */
HWTEST_F(AudioEcManagerUnitTest, IsValidSourcePipe_003, TestSize.Level3)
{
    std::shared_ptr<AudioPipeInfo> pipeInfo = std::make_shared<AudioPipeInfo>();
    pipeInfo->name_ = "invalid_pipe_name";
    EXPECT_FALSE(audioEcManager_->IsValidSourcePipe(pipeInfo, false));
}

/**
 * @tc.name  : IsValidSourcePipe_004
 * @tc.number: AudioEcManagerUnitTest_IsValidSourcePipe_004
 * @tc.desc  : Test IsValidSourcePipe with ec/micref pipe name
 */
HWTEST_F(AudioEcManagerUnitTest, IsValidSourcePipe_004, TestSize.Level2)
{
    std::shared_ptr<AudioPipeInfo> pipeInfo = std::make_shared<AudioPipeInfo>();
    pipeInfo->name_ = "usb_arm_input";
    EXPECT_TRUE(audioEcManager_->IsValidSourcePipe(pipeInfo, true));
}

/**
 * @tc.name  : IsValidSourcePipe_005
 * @tc.number: AudioEcManagerUnitTest_IsValidSourcePipe_005
 * @tc.desc  : Test IsValidSourcePipe with primary_input_AI not in ec/micref list
 */
HWTEST_F(AudioEcManagerUnitTest, IsValidSourcePipe_005, TestSize.Level3)
{
    std::shared_ptr<AudioPipeInfo> pipeInfo = std::make_shared<AudioPipeInfo>();
    pipeInfo->name_ = "primary_input_AI";
    EXPECT_TRUE(audioEcManager_->IsValidSourcePipe(pipeInfo, false));
    EXPECT_FALSE(audioEcManager_->IsValidSourcePipe(pipeInfo, true));
}

/**
 * @tc.name  : CloseNormalSource_001
 * @tc.number: AudioEcManagerUnitTest_CloseNormalSource_001
 * @tc.desc  : Test CloseNormalSource resets normalSourceOpened_ to INVALID
 */
HWTEST_F(AudioEcManagerUnitTest, CloseNormalSource_001, TestSize.Level2)
{
    audioEcManager_->normalSourceOpened_ = SOURCE_TYPE_MIC;
    audioEcManager_->CloseNormalSource();
    EXPECT_EQ(audioEcManager_->GetSourceOpened(), SOURCE_TYPE_INVALID);
}

/**
 * @tc.name  : UpdateStreamCommonInfo_001
 * @tc.number: AudioEcManagerUnitTest_UpdateStreamCommonInfo_001
 * @tc.desc  : Test UpdateStreamCommonInfo with ec disabled calls UpdateModuleInfoForPrimary
 */
HWTEST_F(AudioEcManagerUnitTest, UpdateStreamCommonInfo_001, TestSize.Level2)
{
    audioEcManager_->isEcFeatureEnable_ = false;
    AudioModuleInfo moduleInfo;
    moduleInfo.adapterName = "primary";
    PipeStreamPropInfo targetInfo;
    targetInfo.channels_ = 2;
    targetInfo.sampleRate_ = 48000;
    targetInfo.bufferSize_ = 1920;
    targetInfo.format_ = SAMPLE_S16LE;
    targetInfo.channelLayout_ = CH_LAYOUT_STEREO;
    audioEcManager_->UpdateStreamCommonInfo(moduleInfo, targetInfo, SOURCE_TYPE_MIC);
    EXPECT_EQ(moduleInfo.sourceType, std::to_string(SOURCE_TYPE_MIC));
    EXPECT_EQ(moduleInfo.channels, "2");
    EXPECT_EQ(moduleInfo.rate, "48000");
}

/**
 * @tc.name  : ReloadSourceForInputPipe_001
 * @tc.number: AudioEcManagerUnitTest_ReloadSourceForInputPipe_001
 * @tc.desc  : Test ReloadSourceForInputPipe with nullptr pipe
 */
HWTEST_F(AudioEcManagerUnitTest, ReloadSourceForInputPipe_001, TestSize.Level3)
{
    std::shared_ptr<AudioPipeInfo> pipeInfo = nullptr;
    EXPECT_EQ(audioEcManager_->ReloadSourceForInputPipe(pipeInfo, 0), ERROR);
}

/**
 * @tc.name  : ReloadSourceForInputPipe_002
 * @tc.number: AudioEcManagerUnitTest_ReloadSourceForInputPipe_002
 * @tc.desc  : Test ReloadSourceForInputPipe with pipe that doesn't contain the session
 */
HWTEST_F(AudioEcManagerUnitTest, ReloadSourceForInputPipe_002, TestSize.Level3)
{
    std::shared_ptr<AudioPipeInfo> pipeInfo = std::make_shared<AudioPipeInfo>();
    uint32_t sessionId = 99999;
    EXPECT_EQ(audioEcManager_->ReloadSourceForInputPipe(pipeInfo, sessionId), ERROR);
}

/**
 * @tc.name  : FetchTargetInfoForSessionAdd_001
 * @tc.number: AudioEcManagerUnitTest_FetchTargetInfoForSessionAdd_001
 * @tc.desc  : Test FetchTargetInfoForSessionAdd when adapter info not available
 */
HWTEST_F(AudioEcManagerUnitTest, FetchTargetInfoForSessionAdd_001, TestSize.Level3)
{
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    PipeStreamPropInfo targetInfo;
    SourceType targetSourceType;
    audioEcManager_->audioConfigManager_.isAdapterInfoMap_ = true;
    audioEcManager_->audioConfigManager_.audioPolicyConfig_.adapterInfoMap.clear();
    int32_t ret = audioEcManager_->FetchTargetInfoForSessionAdd(sessionInfo, targetInfo, targetSourceType);
    EXPECT_EQ(ret, ERROR);
}

} // namespace AudioStandard
} // namespace OHOS
