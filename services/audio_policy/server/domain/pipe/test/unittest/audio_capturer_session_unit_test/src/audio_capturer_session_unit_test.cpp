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

#include "audio_capturer_session_unit_test.h"

using namespace testing::ext;

namespace OHOS {
namespace AudioStandard {

void AudioCapturerSessionUnitTest::SetUpTestCase(void) {}
void AudioCapturerSessionUnitTest::TearDownTestCase(void) {}

void AudioCapturerSessionUnitTest::SetUp(void)
{
    audioCapturerSession_ = std::make_shared<AudioCapturerSession>();
    EXPECT_NE(audioCapturerSession_, nullptr);
}

void AudioCapturerSessionUnitTest::TearDown(void)
{
    audioCapturerSession_ = nullptr;
}

/**
 * @tc.name  : Init_001
 * @tc.number: AudioCapturerSessionUnitTest_Init_001
 * @tc.desc  : Test Init stores the a2dp offload manager pointer
 */
HWTEST_F(AudioCapturerSessionUnitTest, Init_001, TestSize.Level2)
{
    auto offloadManager = std::make_shared<AudioA2dpOffloadManager>();
    audioCapturerSession_->Init(offloadManager);
    EXPECT_NE(audioCapturerSession_->audioA2dpOffloadManager_, nullptr);
}

/**
 * @tc.name  : DeInit_001
 * @tc.number: AudioCapturerSessionUnitTest_DeInit_001
 * @tc.desc  : Test DeInit clears the a2dp offload manager pointer
 */
HWTEST_F(AudioCapturerSessionUnitTest, DeInit_001, TestSize.Level2)
{
    auto offloadManager = std::make_shared<AudioA2dpOffloadManager>();
    audioCapturerSession_->Init(offloadManager);
    EXPECT_NE(audioCapturerSession_->audioA2dpOffloadManager_, nullptr);
    audioCapturerSession_->DeInit();
    EXPECT_EQ(audioCapturerSession_->audioA2dpOffloadManager_, nullptr);
}

/**
 * @tc.name  : SetConfigParserFlag_001
 * @tc.number: AudioCapturerSessionUnitTest_SetConfigParserFlag_001
 * @tc.desc  : Test SetConfigParserFlag sets isPolicyConfigParsered_ to true
 */
HWTEST_F(AudioCapturerSessionUnitTest, SetConfigParserFlag_001, TestSize.Level2)
{
    EXPECT_FALSE(audioCapturerSession_->isPolicyConfigParsered_);
    audioCapturerSession_->SetConfigParserFlag();
    EXPECT_TRUE(audioCapturerSession_->isPolicyConfigParsered_);
}

/**
 * @tc.name  : GetCapturerState_001
 * @tc.number: AudioCapturerSessionUnitTest_GetCapturerState_001
 * @tc.desc  : Test GetCapturerState with no sessions returns CAPTURER_INVALID
 */
HWTEST_F(AudioCapturerSessionUnitTest, GetCapturerState_001, TestSize.Level3)
{
    audioCapturerSession_->sessionWithNormalSourceType_.clear();
    audioCapturerSession_->sessionWithSpecialSourceType_.clear();
    CapturerState state = audioCapturerSession_->GetCapturerState();
    EXPECT_NE(audioCapturerSession_, nullptr);
}

/**
 * @tc.name  : SetHearingAidReloadFlag_001
 * @tc.number: AudioCapturerSessionUnitTest_SetHearingAidReloadFlag_001
 * @tc.desc  : Test SetHearingAidReloadFlag sets the flag correctly
 */
HWTEST_F(AudioCapturerSessionUnitTest, SetHearingAidReloadFlag_001, TestSize.Level2)
{
    int32_t ret = audioCapturerSession_->SetHearingAidReloadFlag(true);
    EXPECT_EQ(ret, SUCCESS);
    EXPECT_TRUE(audioCapturerSession_->hearingAidReloadFlag_);

    ret = audioCapturerSession_->SetHearingAidReloadFlag(false);
    EXPECT_EQ(ret, SUCCESS);
    EXPECT_FALSE(audioCapturerSession_->hearingAidReloadFlag_);
}

/**
 * @tc.name  : IsInvalidPipeRole_001
 * @tc.number: AudioCapturerSessionUnitTest_IsInvalidPipeRole_001
 * @tc.desc  : Test IsInvalidPipeRole returns true for non-input pipe role
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsInvalidPipeRole_001, TestSize.Level3)
{
    auto pipe = std::make_shared<AudioPipeInfo>();
    pipe->pipeRole_ = PIPE_ROLE_OUTPUT;
    EXPECT_TRUE(audioCapturerSession_->IsInvalidPipeRole(pipe));
}

/**
 * @tc.name  : IsInvalidPipeRole_002
 * @tc.number: AudioCapturerSessionUnitTest_IsInvalidPipeRole_002
 * @tc.desc  : Test IsInvalidPipeRole returns false for input pipe role
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsInvalidPipeRole_002, TestSize.Level3)
{
    auto pipe = std::make_shared<AudioPipeInfo>();
    pipe->pipeRole_ = PIPE_ROLE_INPUT;
    EXPECT_FALSE(audioCapturerSession_->IsInvalidPipeRole(pipe));
}

/**
 * @tc.name  : IsIndependentPipe_001
 * @tc.number: AudioCapturerSessionUnitTest_IsIndependentPipe_001
 * @tc.desc  : Test IsIndependentPipe returns false for nullptr pipe
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsIndependentPipe_001, TestSize.Level3)
{
    std::shared_ptr<AudioPipeInfo> pipe = nullptr;
    EXPECT_FALSE(audioCapturerSession_->IsIndependentPipe(pipe));
}

/**
 * @tc.name  : IsIndependentPipe_002
 * @tc.number: AudioCapturerSessionUnitTest_IsIndependentPipe_002
 * @tc.desc  : Test IsIndependentPipe returns true for VA adapter type
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsIndependentPipe_002, TestSize.Level3)
{
    auto pipe = std::make_shared<AudioPipeInfo>();
    pipe->adapterName_ = "va";
    EXPECT_TRUE(audioCapturerSession_->IsIndependentPipe(pipe));
}

/**
 * @tc.name  : IsIndependentPipe_003
 * @tc.number: AudioCapturerSessionUnitTest_IsIndependentPipe_003
 * @tc.desc  : Test IsIndependentPipe returns false for non-VA adapter type
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsIndependentPipe_003, TestSize.Level3)
{
    auto pipe = std::make_shared<AudioPipeInfo>();
    pipe->adapterName_ = "primary";
    EXPECT_FALSE(audioCapturerSession_->IsIndependentPipe(pipe));
}

/**
 * @tc.name  : IsValidSessionIdForReload_001
 * @tc.number: AudioCapturerSessionUnitTest_IsValidSessionIdForReload_001
 * @tc.desc  : Test IsValidSessionIdForReload returns false for unknown session
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsValidSessionIdForReload_001, TestSize.Level3)
{
    audioCapturerSession_->sessionWithNormalSourceType_.clear();
    EXPECT_FALSE(audioCapturerSession_->IsValidSessionIdForReload(12345));
}

/**
 * @tc.name  : IsValidSessionIdForReload_002
 * @tc.number: AudioCapturerSessionUnitTest_IsValidSessionIdForReload_002
 * @tc.desc  : Test IsValidSessionIdForReload returns true for valid normal session
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsValidSessionIdForReload_002, TestSize.Level2)
{
    uint32_t sessionId = 1001;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId] = sessionInfo;
    EXPECT_TRUE(audioCapturerSession_->IsValidSessionIdForReload(sessionId));
}

/**
 * @tc.name  : IsValidSessionIdForReload_003
 * @tc.number: AudioCapturerSessionUnitTest_IsValidSessionIdForReload_003
 * @tc.desc  : Test IsValidSessionIdForReload returns false for special source type
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsValidSessionIdForReload_003, TestSize.Level3)
{
    uint32_t sessionId = 1001;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_PLAYBACK_CAPTURE;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId] = sessionInfo;
    EXPECT_FALSE(audioCapturerSession_->IsValidSessionIdForReload(sessionId));
}

/**
 * @tc.name  : IsValidSessionIdForReload_004
 * @tc.number: AudioCapturerSessionUnitTest_IsValidSessionIdForReload_004
 * @tc.desc  : Test IsValidSessionIdForReload returns false for SOURCE_TYPE_WAKEUP
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsValidSessionIdForReload_004, TestSize.Level3)
{
    uint32_t sessionId = 1002;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_WAKEUP;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId] = sessionInfo;
    EXPECT_FALSE(audioCapturerSession_->IsValidSessionIdForReload(sessionId));
}

/**
 * @tc.name  : IsSourceTypeValidForEc_001
 * @tc.number: AudioCapturerSessionUnitTest_IsSourceTypeValidForEc_001
 * @tc.desc  : Test IsSourceTypeValidForEc for valid source types
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsSourceTypeValidForEc_001, TestSize.Level2)
{
    EXPECT_TRUE(audioCapturerSession_->IsSourceTypeValidForEc(SOURCE_TYPE_VOICE_COMMUNICATION));
    EXPECT_TRUE(audioCapturerSession_->IsSourceTypeValidForEc(SOURCE_TYPE_MIC));
}

/**
 * @tc.name  : IsSourceTypeValidForEc_002
 * @tc.number: AudioCapturerSessionUnitTest_IsSourceTypeValidForEc_002
 * @tc.desc  : Test IsSourceTypeValidForEc for invalid source types
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsSourceTypeValidForEc_002, TestSize.Level3)
{
    EXPECT_FALSE(audioCapturerSession_->IsSourceTypeValidForEc(SOURCE_TYPE_INVALID));
    EXPECT_FALSE(audioCapturerSession_->IsSourceTypeValidForEc(SOURCE_TYPE_CAMCORDER));
    EXPECT_FALSE(audioCapturerSession_->IsSourceTypeValidForEc(SOURCE_TYPE_VOICE_CALL));
    EXPECT_FALSE(audioCapturerSession_->IsSourceTypeValidForEc(SOURCE_TYPE_PLAYBACK_CAPTURE));
}

/**
 * @tc.name  : IsSessionIdValidForEc_001
 * @tc.number: AudioCapturerSessionUnitTest_IsSessionIdValidForEc_001
 * @tc.desc  : Test IsSessionIdValidForEc returns true when session exists
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsSessionIdValidForEc_001, TestSize.Level2)
{
    uint32_t sessionId = 1001;
    SessionInfo sessionInfo;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId] = sessionInfo;
    EXPECT_TRUE(audioCapturerSession_->IsSessionIdValidForEc(sessionId));
}

/**
 * @tc.name  : IsSessionIdValidForEc_002
 * @tc.number: AudioCapturerSessionUnitTest_IsSessionIdValidForEc_002
 * @tc.desc  : Test IsSessionIdValidForEc returns false when session doesn't exist
 */
HWTEST_F(AudioCapturerSessionUnitTest, IsSessionIdValidForEc_002, TestSize.Level3)
{
    audioCapturerSession_->sessionWithNormalSourceType_.clear();
    EXPECT_FALSE(audioCapturerSession_->IsSessionIdValidForEc(99999));
}

/**
 * @tc.name  : OnCapturerSessionRemoved_001
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionRemoved_001
 * @tc.desc  : Test OnCapturerSessionRemoved for special source type (REMOTE_CAST)
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionRemoved_001, TestSize.Level2)
{
    uint64_t sessionId = 1001;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_WAKEUP;
    audioCapturerSession_->sessionWithSpecialSourceType_[sessionId] = sessionInfo;
    audioCapturerSession_->OnCapturerSessionRemoved(sessionId);
    EXPECT_EQ(audioCapturerSession_->sessionWithSpecialSourceType_.count(sessionId), 0);
}

/**
 * @tc.name  : OnCapturerSessionRemoved_002
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionRemoved_002
 * @tc.desc  : Test OnCapturerSessionRemoved for normal source type with remaining sessions
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionRemoved_002, TestSize.Level2)
{
    uint64_t sessionId1 = 1001;
    uint64_t sessionId2 = 1002;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId1] = sessionInfo;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId2] = sessionInfo;
    audioCapturerSession_->OnCapturerSessionRemoved(sessionId1);
    EXPECT_EQ(audioCapturerSession_->sessionWithNormalSourceType_.count(sessionId1), 0);
    EXPECT_EQ(audioCapturerSession_->sessionWithNormalSourceType_.count(sessionId2), 1);
}

/**
 * @tc.name  : OnCapturerSessionRemoved_003
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionRemoved_003
 * @tc.desc  : Test OnCapturerSessionRemoved for last normal source session closes normal source
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionRemoved_003, TestSize.Level2)
{
    uint64_t sessionId = 1001;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId] = sessionInfo;
    audioCapturerSession_->audioEcManager_.normalSourceOpened_ = SOURCE_TYPE_MIC;
    audioCapturerSession_->OnCapturerSessionRemoved(sessionId);
    EXPECT_EQ(audioCapturerSession_->sessionWithNormalSourceType_.count(sessionId), 0);
    EXPECT_EQ(audioCapturerSession_->audioEcManager_.GetSourceOpened(), SOURCE_TYPE_INVALID);
}

/**
 * @tc.name  : OnCapturerSessionRemoved_004
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionRemoved_004
 * @tc.desc  : Test OnCapturerSessionRemoved for voice communication resets ec info
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionRemoved_004, TestSize.Level2)
{
    uint64_t sessionId1 = 1001;
    uint64_t sessionId2 = 1002;
    SessionInfo sessionInfo1;
    sessionInfo1.sourceType = SOURCE_TYPE_VOICE_COMMUNICATION;
    SessionInfo sessionInfo2;
    sessionInfo2.sourceType = SOURCE_TYPE_MIC;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId1] = sessionInfo1;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId2] = sessionInfo2;
    audioCapturerSession_->OnCapturerSessionRemoved(sessionId1);
    AudioEcInfo ecInfo = audioCapturerSession_->audioEcManager_.GetAudioEcInfo();
    EXPECT_EQ(ecInfo.inputDevice.deviceType_, DEVICE_TYPE_NONE);
}

/**
 * @tc.name  : OnCapturerSessionRemoved_005
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionRemoved_005
 * @tc.desc  : Test OnCapturerSessionRemoved with inputPipeRouteFlag session
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionRemoved_005, TestSize.Level3)
{
    uint64_t sessionId = 2001;
    audioCapturerSession_->sessionWithInputPipeRouteFlag_[sessionId] = AUDIO_INPUT_FLAG_NORMAL;
    audioCapturerSession_->OnCapturerSessionRemoved(sessionId);
    EXPECT_EQ(audioCapturerSession_->sessionWithInputPipeRouteFlag_.count(sessionId), 0);
}

/**
 * @tc.name  : OnCapturerSessionRemoved_006
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionRemoved_006
 * @tc.desc  : Test OnCapturerSessionRemoved for unknown session adds to removed set
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionRemoved_006, TestSize.Level3)
{
    uint64_t sessionId = 9999;
    audioCapturerSession_->sessionWithNormalSourceType_.clear();
    audioCapturerSession_->sessionWithSpecialSourceType_.clear();
    audioCapturerSession_->sessionWithInputPipeRouteFlag_.clear();
    audioCapturerSession_->OnCapturerSessionRemoved(sessionId);
    EXPECT_EQ(audioCapturerSession_->sessionIdisRemovedSet_.count(sessionId), 1);
}

/**
 * @tc.name  : OnCapturerSessionAdded_001
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionAdded_001
 * @tc.desc  : Test OnCapturerSessionAdded when policy config is not parsed
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionAdded_001, TestSize.Level3)
{
    audioCapturerSession_->isPolicyConfigParsered_ = false;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    AudioStreamInfo streamInfo;
    int32_t ret = audioCapturerSession_->OnCapturerSessionAdded(1001, sessionInfo, streamInfo);
    EXPECT_EQ(ret, ERROR);
}

/**
 * @tc.name  : OnCapturerSessionAdded_002
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionAdded_002
 * @tc.desc  : Test OnCapturerSessionAdded when sessionId was already removed
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionAdded_002, TestSize.Level3)
{
    audioCapturerSession_->isPolicyConfigParsered_ = true;
    audioCapturerSession_->audioVolumeManager_.SetLoadFlag(true);
    uint64_t sessionId = 1001;
    audioCapturerSession_->sessionIdisRemovedSet_.insert(sessionId);
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    AudioStreamInfo streamInfo;
    int32_t ret = audioCapturerSession_->OnCapturerSessionAdded(sessionId, sessionInfo, streamInfo);
    EXPECT_EQ(ret, SUCCESS);
    EXPECT_EQ(audioCapturerSession_->sessionIdisRemovedSet_.count(sessionId), 0);
}

/**
 * @tc.name  : OnCapturerSessionAdded_003
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionAdded_003
 * @tc.desc  : Test OnCapturerSessionAdded with special source type (WAKEUP)
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionAdded_003, TestSize.Level2)
{
    audioCapturerSession_->isPolicyConfigParsered_ = true;
    audioCapturerSession_->audioVolumeManager_.SetLoadFlag(true);
    uint64_t sessionId = 2001;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_WAKEUP;
    AudioStreamInfo streamInfo;
    int32_t ret = audioCapturerSession_->OnCapturerSessionAdded(sessionId, sessionInfo, streamInfo);
    EXPECT_EQ(audioCapturerSession_->sessionWithSpecialSourceType_.count(sessionId), 1);
}

/**
 * @tc.name  : OnCapturerSessionAdded_004
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionAdded_004
 * @tc.desc  : Test OnCapturerSessionAdded with normal source type when source already opened
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionAdded_004, TestSize.Level2)
{
    audioCapturerSession_->isPolicyConfigParsered_ = true;
    audioCapturerSession_->audioVolumeManager_.SetLoadFlag(true);
    audioCapturerSession_->audioEcManager_.normalSourceOpened_ = SOURCE_TYPE_MIC;
    uint64_t sessionId = 3001;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    AudioStreamInfo streamInfo;
    int32_t ret = audioCapturerSession_->OnCapturerSessionAdded(sessionId, sessionInfo, streamInfo);
    EXPECT_EQ(ret, SUCCESS);
    EXPECT_EQ(audioCapturerSession_->sessionWithNormalSourceType_.count(sessionId), 1);
}

/**
 * @tc.name  : OnCapturerSessionAdded_005
 * @tc.number: AudioCapturerSessionUnitTest_OnCapturerSessionAdded_005
 * @tc.desc  : Test OnCapturerSessionAdded with normal source type when source is not opened
 */
HWTEST_F(AudioCapturerSessionUnitTest, OnCapturerSessionAdded_005, TestSize.Level3)
{
    audioCapturerSession_->isPolicyConfigParsered_ = true;
    audioCapturerSession_->audioVolumeManager_.SetLoadFlag(true);
    audioCapturerSession_->audioEcManager_.normalSourceOpened_ = SOURCE_TYPE_INVALID;
    uint64_t sessionId = 4001;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    AudioStreamInfo streamInfo;
    int32_t ret = audioCapturerSession_->OnCapturerSessionAdded(sessionId, sessionInfo, streamInfo);
    EXPECT_EQ(ret, SUCCESS);
}

/**
 * @tc.name  : ConstructWakeupAudioModuleInfo_004
 * @tc.number: AudioCapturerSessionUnitTest_ConstructWakeupAudioModuleInfo_004
 * @tc.desc  : Test ConstructWakeupAudioModuleInfo when adapter info flag is not set
 */
HWTEST_F(AudioCapturerSessionUnitTest, ConstructWakeupAudioModuleInfo_004, TestSize.Level3)
{
    audioCapturerSession_->audioConfigManager_.isAdapterInfoMap_ = false;
    AudioStreamInfo streamInfo;
    AudioModuleInfo audioModuleInfo;
    EXPECT_FALSE(audioCapturerSession_->ConstructWakeupAudioModuleInfo(streamInfo, audioModuleInfo));
}

/**
 * @tc.name  : FillWakeupStreamPropInfo_001
 * @tc.number: AudioCapturerSessionUnitTest_FillWakeupStreamPropInfo_001
 * @tc.desc  : Test FillWakeupStreamPropInfo with nullptr pipe info
 */
HWTEST_F(AudioCapturerSessionUnitTest, FillWakeupStreamPropInfo_001, TestSize.Level3)
{
    AudioStreamInfo streamInfo;
    std::shared_ptr<AdapterPipeInfo> pipeInfo = nullptr;
    AudioModuleInfo audioModuleInfo;
    EXPECT_FALSE(audioCapturerSession_->FillWakeupStreamPropInfo(streamInfo, pipeInfo, audioModuleInfo));
}

/**
 * @tc.name  : FillWakeupStreamPropInfo_002
 * @tc.number: AudioCapturerSessionUnitTest_FillWakeupStreamPropInfo_002
 * @tc.desc  : Test FillWakeupStreamPropInfo with empty stream prop infos
 */
HWTEST_F(AudioCapturerSessionUnitTest, FillWakeupStreamPropInfo_002, TestSize.Level3)
{
    AudioStreamInfo streamInfo;
    auto pipeInfo = std::make_shared<AdapterPipeInfo>();
    pipeInfo->streamPropInfos_.clear();
    AudioModuleInfo audioModuleInfo;
    EXPECT_FALSE(audioCapturerSession_->FillWakeupStreamPropInfo(streamInfo, pipeInfo, audioModuleInfo));
}

/**
 * @tc.name  : GetEnhancePropByName_002
 * @tc.number: AudioCapturerSessionUnitTest_GetEnhancePropByName_002
 * @tc.desc  : Test GetEnhancePropByName returns matching property value
 */
HWTEST_F(AudioCapturerSessionUnitTest, GetEnhancePropByName_002, TestSize.Level2)
{
    AudioEnhancePropertyArray propertyArray;
    AudioEnhanceProperty prop1;
    prop1.enhanceClass = "record";
    prop1.enhanceProp = "NRON";
    propertyArray.property.push_back(prop1);
    AudioEnhanceProperty prop2;
    prop2.enhanceClass = "voip_up";
    prop2.enhanceProp = "PNR";
    propertyArray.property.push_back(prop2);

    EXPECT_EQ(audioCapturerSession_->GetEnhancePropByName(propertyArray, "record"), "NRON");
    EXPECT_EQ(audioCapturerSession_->GetEnhancePropByName(propertyArray, "voip_up"), "PNR");
    EXPECT_EQ(audioCapturerSession_->GetEnhancePropByName(propertyArray, "unknown"), "");
}

/**
 * @tc.name  : GetEnhancePropByNameV3_001
 * @tc.number: AudioCapturerSessionUnitTest_GetEnhancePropByNameV3_001
 * @tc.desc  : Test GetEnhancePropByNameV3 returns matching property value
 */
HWTEST_F(AudioCapturerSessionUnitTest, GetEnhancePropByNameV3_001, TestSize.Level2)
{
    AudioEffectPropertyArrayV3 propertyArray;
    AudioEffectPropertyV3 prop1;
    prop1.name = "record";
    prop1.category = "NRON";
    propertyArray.property.push_back(prop1);
    AudioEffectPropertyV3 prop2;
    prop2.name = "voip_up";
    prop2.category = "PNR";
    propertyArray.property.push_back(prop2);

    EXPECT_EQ(audioCapturerSession_->GetEnhancePropByNameV3(propertyArray, "record"), "NRON");
    EXPECT_EQ(audioCapturerSession_->GetEnhancePropByNameV3(propertyArray, "voip_up"), "PNR");
    EXPECT_EQ(audioCapturerSession_->GetEnhancePropByNameV3(propertyArray, "unknown"), "");
}

/**
 * @tc.name  : ReloadSourceForEffect_EnhanceV1_001
 * @tc.number: AudioCapturerSessionUnitTest_ReloadSourceForEffect_EnhanceV1_001
 * @tc.desc  : Test ReloadSourceForEffect (AudioEnhancePropertyArray) when micRef feature disabled
 */
HWTEST_F(AudioCapturerSessionUnitTest, ReloadSourceForEffect_EnhanceV1_001, TestSize.Level3)
{
    AudioEnhancePropertyArray oldPropertyArray;
    AudioEnhancePropertyArray newPropertyArray;
    audioCapturerSession_->audioEcManager_.isMicRefFeatureEnable_ = false;
    EXPECT_NO_THROW(audioCapturerSession_->ReloadSourceForEffect(oldPropertyArray, newPropertyArray));
}

/**
 * @tc.name  : ReloadSourceForEffect_V3_001
 * @tc.number: AudioCapturerSessionUnitTest_ReloadSourceForEffect_V3_001
 * @tc.desc  : Test ReloadSourceForEffect (AudioEffectPropertyArrayV3) when micRef feature disabled
 */
HWTEST_F(AudioCapturerSessionUnitTest, ReloadSourceForEffect_V3_001, TestSize.Level3)
{
    AudioEffectPropertyArrayV3 oldPropertyArray;
    AudioEffectPropertyArrayV3 newPropertyArray;
    audioCapturerSession_->audioEcManager_.isMicRefFeatureEnable_ = false;
    EXPECT_NO_THROW(audioCapturerSession_->ReloadSourceForEffect(oldPropertyArray, newPropertyArray));
}

/**
 * @tc.name  : ReloadSourceForDeviceChange_002
 * @tc.number: AudioCapturerSessionUnitTest_ReloadSourceForDeviceChange_002
 * @tc.desc  : Test ReloadSourceForDeviceChange when ec feature is disabled
 */
HWTEST_F(AudioCapturerSessionUnitTest, ReloadSourceForDeviceChange_002, TestSize.Level3)
{
    AudioDeviceDescriptor inputDevice;
    AudioDeviceDescriptor outputDevice;
    std::string caller = "test";
    audioCapturerSession_->audioEcManager_.isEcFeatureEnable_ = false;
    EXPECT_NO_THROW(audioCapturerSession_->ReloadSourceForDeviceChange(inputDevice, outputDevice, caller));
}

/**
 * @tc.name  : SetInputDeviceTypeForReload_001
 * @tc.number: AudioCapturerSessionUnitTest_SetInputDeviceTypeForReload_001
 * @tc.desc  : Test SetInputDeviceTypeForReload and GetInputDeviceTypeForReload
 */
HWTEST_F(AudioCapturerSessionUnitTest, SetInputDeviceTypeForReload_001, TestSize.Level2)
{
    AudioDeviceDescriptor inputDevice;
    inputDevice.deviceType_ = DEVICE_TYPE_USB_HEADSET;
    audioCapturerSession_->SetInputDeviceTypeForReload(inputDevice);
    const AudioDeviceDescriptor &result = audioCapturerSession_->GetInputDeviceTypeForReload();
    EXPECT_EQ(result.deviceType_, DEVICE_TYPE_USB_HEADSET);
}

/**
 * @tc.name  : FindRemainingNormalSession_001
 * @tc.number: AudioCapturerSessionUnitTest_FindRemainingNormalSession_001
 * @tc.desc  : Test FindRemainingNormalSession when findRunningSessionRet is true returns true immediately
 */
HWTEST_F(AudioCapturerSessionUnitTest, FindRemainingNormalSession_001, TestSize.Level2)
{
    uint32_t targetSessionId = 0;
    bool result = audioCapturerSession_->FindRemainingNormalSession(1001, true, 1002, targetSessionId);
    EXPECT_TRUE(result);
    EXPECT_EQ(targetSessionId, 1002);
}

/**
 * @tc.name  : FindRemainingNormalSession_002
 * @tc.number: AudioCapturerSessionUnitTest_FindRemainingNormalSession_002
 * @tc.desc  : Test FindRemainingNormalSession when no remaining sessions exist
 */
HWTEST_F(AudioCapturerSessionUnitTest, FindRemainingNormalSession_002, TestSize.Level3)
{
    audioCapturerSession_->sessionWithNormalSourceType_.clear();
    uint32_t targetSessionId = 0;
    bool result = audioCapturerSession_->FindRemainingNormalSession(1001, false, 0, targetSessionId);
    EXPECT_FALSE(result);
}

/**
 * @tc.name  : FindRemainingNormalSession_003
 * @tc.number: AudioCapturerSessionUnitTest_FindRemainingNormalSession_003
 * @tc.desc  : Test FindRemainingNormalSession picks highest priority remaining session
 */
HWTEST_F(AudioCapturerSessionUnitTest, FindRemainingNormalSession_003, TestSize.Level2)
{
    uint32_t removedSessionId = 1001;
    uint32_t remainSession1 = 1002;
    uint32_t remainSession2 = 1003;
    SessionInfo info1;
    info1.sourceType = SOURCE_TYPE_MIC;
    SessionInfo info2;
    info2.sourceType = SOURCE_TYPE_VOICE_COMMUNICATION;
    audioCapturerSession_->sessionWithNormalSourceType_[removedSessionId] = info1;
    audioCapturerSession_->sessionWithNormalSourceType_[remainSession1] = info1;
    audioCapturerSession_->sessionWithNormalSourceType_[remainSession2] = info2;

    uint32_t targetSessionId = 0;
    bool result = audioCapturerSession_->FindRemainingNormalSession(removedSessionId, false, 0, targetSessionId);
    EXPECT_TRUE(result);
    EXPECT_EQ(targetSessionId, remainSession2);
}

/**
 * @tc.name  : ReloadCaptureSession_005
 * @tc.number: AudioCapturerSessionUnitTest_ReloadCaptureSession_005
 * @tc.desc  : Test ReloadCaptureSession returns SUCCESS when hearingAidReloadFlag is true
 */
HWTEST_F(AudioCapturerSessionUnitTest, ReloadCaptureSession_005, TestSize.Level3)
{
    audioCapturerSession_->hearingAidReloadFlag_ = true;
    uint32_t sessionId = 1001;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    audioCapturerSession_->sessionWithNormalSourceType_[sessionId] = sessionInfo;
    EXPECT_EQ(audioCapturerSession_->ReloadCaptureSession(sessionId, SESSION_OPERATION_START), SUCCESS);
}

/**
 * @tc.name  : CloseWakeUpAudioCapturer_001
 * @tc.number: AudioCapturerSessionUnitTest_CloseWakeUpAudioCapturer_001
 * @tc.desc  : Test CloseWakeUpAudioCapturer
 */
HWTEST_F(AudioCapturerSessionUnitTest, CloseWakeUpAudioCapturer_001, TestSize.Level2)
{
    int32_t ret = audioCapturerSession_->CloseWakeUpAudioCapturer();
    EXPECT_NE(audioCapturerSession_, nullptr);
}

} // namespace AudioStandard
} // namespace OHOS
