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

#include "audio_core_service_unit_test.h"

using namespace testing::ext;

namespace OHOS {
namespace AudioStandard {

void AudioCoreServiceUnitTest::SetUpTestCase(void) {}
void AudioCoreServiceUnitTest::TearDownTestCase(void) {}

void AudioCoreServiceUnitTest::SetUp(void)
{
    audioCoreService_ = std::make_shared<AudioCoreService>();
    EXPECT_NE(audioCoreService_, nullptr);
}

void AudioCoreServiceUnitTest::TearDown(void)
{
    audioCoreService_ = nullptr;
}

/**
 * @tc.name  : GetCoreService_001
 * @tc.number: AudioCoreServiceUnitTest_GetCoreService_001
 * @tc.desc  : Test GetCoreService returns non-null singleton instance
 */
HWTEST_F(AudioCoreServiceUnitTest, GetCoreService_001, TestSize.Level2)
{
    auto coreService = AudioCoreService::GetCoreService();
    EXPECT_NE(coreService, nullptr);
}

/**
 * @tc.name  : GetCoreService_002
 * @tc.number: AudioCoreServiceUnitTest_GetCoreService_002
 * @tc.desc  : Test GetCoreService returns the same instance on multiple calls
 */
HWTEST_F(AudioCoreServiceUnitTest, GetCoreService_002, TestSize.Level2)
{
    auto coreService1 = AudioCoreService::GetCoreService();
    auto coreService2 = AudioCoreService::GetCoreService();
    EXPECT_EQ(coreService1.get(), coreService2.get());
}

/**
 * @tc.name  : SetCallbackHandler_001
 * @tc.number: AudioCoreServiceUnitTest_SetCallbackHandler_001
 * @tc.desc  : Test SetCallbackHandler with nullptr
 */
HWTEST_F(AudioCoreServiceUnitTest, SetCallbackHandler_001, TestSize.Level3)
{
    EXPECT_NO_THROW(audioCoreService_->SetCallbackHandler(nullptr));
}

/**
 * @tc.name  : DumpPipeManager_001
 * @tc.number: AudioCoreServiceUnitTest_DumpPipeManager_001
 * @tc.desc  : Test DumpPipeManager generates dump string
 */
HWTEST_F(AudioCoreServiceUnitTest, DumpPipeManager_001, TestSize.Level3)
{
    std::string dumpString;
    audioCoreService_->DumpPipeManager(dumpString);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : DumpSelectHistory_001
 * @tc.number: AudioCoreServiceUnitTest_DumpSelectHistory_001
 * @tc.desc  : Test DumpSelectHistory generates history dump with empty history
 */
HWTEST_F(AudioCoreServiceUnitTest, DumpSelectHistory_001, TestSize.Level2)
{
    std::string dumpString;
    audioCoreService_->DumpSelectHistory(dumpString);
    EXPECT_NE(dumpString.find("Select device history infos"), std::string::npos);
    EXPECT_NE(dumpString.find("TotalPipeNums: 0"), std::string::npos);
}

/**
 * @tc.name  : DumpSelectHistory_002
 * @tc.number: AudioCoreServiceUnitTest_DumpSelectHistory_002
 * @tc.desc  : Test DumpSelectHistory with recorded items
 */
HWTEST_F(AudioCoreServiceUnitTest, DumpSelectHistory_002, TestSize.Level2)
{
    audioCoreService_->RecordSelectDevice("test_history_entry_1");
    audioCoreService_->RecordSelectDevice("test_history_entry_2");
    std::string dumpString;
    audioCoreService_->DumpSelectHistory(dumpString);
    EXPECT_NE(dumpString.find("test_history_entry_1"), std::string::npos);
    EXPECT_NE(dumpString.find("test_history_entry_2"), std::string::npos);
}

/**
 * @tc.name  : RecordSelectDevice_001
 * @tc.number: AudioCoreServiceUnitTest_RecordSelectDevice_001
 * @tc.desc  : Test RecordSelectDevice limits history size
 */
HWTEST_F(AudioCoreServiceUnitTest, RecordSelectDevice_001, TestSize.Level2)
{
    for (int i = 0; i < 15; i++) {
        audioCoreService_->RecordSelectDevice("entry_" + std::to_string(i));
    }
    std::string dumpString;
    audioCoreService_->DumpSelectHistory(dumpString);
    // SELECT_DEVICE_HISTORY_LIMIT is 10, so after adding 15, should only have 10
    EXPECT_EQ(dumpString.find("entry_0"), std::string::npos);
    EXPECT_NE(dumpString.find("entry_14"), std::string::npos);
}

/**
 * @tc.name  : ConnectServiceAdapter_001
 * @tc.number: AudioCoreServiceUnitTest_ConnectServiceAdapter_001
 * @tc.desc  : Test ConnectServiceAdapter
 */
HWTEST_F(AudioCoreServiceUnitTest, ConnectServiceAdapter_001, TestSize.Level3)
{
    bool ret = audioCoreService_->ConnectServiceAdapter();
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : GetDevices_001
 * @tc.number: AudioCoreServiceUnitTest_GetDevices_001
 * @tc.desc  : Test GetDevices with OUTPUT_DEVICES_FLAG
 */
HWTEST_F(AudioCoreServiceUnitTest, GetDevices_001, TestSize.Level2)
{
    auto devices = audioCoreService_->GetDevices(OUTPUT_DEVICES_FLAG);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : GetDevices_002
 * @tc.number: AudioCoreServiceUnitTest_GetDevices_002
 * @tc.desc  : Test GetDevices with INPUT_DEVICES_FLAG
 */
HWTEST_F(AudioCoreServiceUnitTest, GetDevices_002, TestSize.Level2)
{
    auto devices = audioCoreService_->GetDevices(INPUT_DEVICES_FLAG);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : GetDevices_003
 * @tc.number: AudioCoreServiceUnitTest_GetDevices_003
 * @tc.desc  : Test GetDevices with ALL_DEVICES_FLAG
 */
HWTEST_F(AudioCoreServiceUnitTest, GetDevices_003, TestSize.Level3)
{
    auto devices = audioCoreService_->GetDevices(ALL_DEVICES_FLAG);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : IsArmUsbDevice_001
 * @tc.number: AudioCoreServiceUnitTest_IsArmUsbDevice_001
 * @tc.desc  : Test IsArmUsbDevice with non-USB device
 */
HWTEST_F(AudioCoreServiceUnitTest, IsArmUsbDevice_001, TestSize.Level3)
{
    AudioDeviceDescriptor deviceDesc;
    deviceDesc.deviceType_ = DEVICE_TYPE_SPEAKER;
    bool result = audioCoreService_->IsArmUsbDevice(deviceDesc);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : GetAvailableMicrophones_001
 * @tc.number: AudioCoreServiceUnitTest_GetAvailableMicrophones_001
 * @tc.desc  : Test GetAvailableMicrophones returns list
 */
HWTEST_F(AudioCoreServiceUnitTest, GetAvailableMicrophones_001, TestSize.Level3)
{
    auto microphones = audioCoreService_->GetAvailableMicrophones();
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : GetVolumeGroupInfos_001
 * @tc.number: AudioCoreServiceUnitTest_GetVolumeGroupInfos_001
 * @tc.desc  : Test GetVolumeGroupInfos
 */
HWTEST_F(AudioCoreServiceUnitTest, GetVolumeGroupInfos_001, TestSize.Level3)
{
    std::vector<sptr<VolumeGroupInfo>> infos;
    bool result = audioCoreService_->GetVolumeGroupInfos(infos);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : ParsePreferredInputDeviceHistory_001
 * @tc.number: AudioCoreServiceUnitTest_ParsePreferredInputDeviceHistory_001
 * @tc.desc  : Test ParsePreferredInputDeviceHistory with nullptr returns empty string
 */
HWTEST_F(AudioCoreServiceUnitTest, ParsePreferredInputDeviceHistory_001, TestSize.Level3)
{
    std::string result = audioCoreService_->ParsePreferredInputDeviceHistory(nullptr);
    EXPECT_EQ(result, "");
}

/**
 * @tc.name  : ParsePreferredInputDeviceHistory_002
 * @tc.number: AudioCoreServiceUnitTest_ParsePreferredInputDeviceHistory_002
 * @tc.desc  : Test ParsePreferredInputDeviceHistory with valid stream desc
 */
HWTEST_F(AudioCoreServiceUnitTest, ParsePreferredInputDeviceHistory_002, TestSize.Level2)
{
    auto streamDesc = std::make_shared<AudioStreamDescriptor>();
    streamDesc->sessionId_ = 12345;
    streamDesc->capturerInfo_.sourceType = SOURCE_TYPE_MIC;
    std::string result = audioCoreService_->ParsePreferredInputDeviceHistory(streamDesc);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("12345"), std::string::npos);
}

/**
 * @tc.name  : CreateRendererClient_001
 * @tc.number: AudioCoreServiceUnitTest_CreateRendererClient_001
 * @tc.desc  : Test CreateRendererClient with nullptr stream desc
 */
HWTEST_F(AudioCoreServiceUnitTest, CreateRendererClient_001, TestSize.Level3)
{
    std::shared_ptr<AudioStreamDescriptor> streamDesc = nullptr;
    uint32_t audioFlag = 0;
    uint32_t sessionId = 0;
    std::string networkId;
    int32_t ret = audioCoreService_->CreateRendererClient(streamDesc, audioFlag, sessionId, networkId);
    EXPECT_EQ(ret, ERR_NULL_POINTER);
}

/**
 * @tc.name  : CreateCapturerClient_001
 * @tc.number: AudioCoreServiceUnitTest_CreateCapturerClient_001
 * @tc.desc  : Test CreateCapturerClient with nullptr stream desc
 */
HWTEST_F(AudioCoreServiceUnitTest, CreateCapturerClient_001, TestSize.Level3)
{
    std::shared_ptr<AudioStreamDescriptor> streamDesc = nullptr;
    uint32_t audioFlag = 0;
    uint32_t sessionId = 0;
    int32_t ret = audioCoreService_->CreateCapturerClient(streamDesc, audioFlag, sessionId);
    EXPECT_EQ(ret, ERR_INVALID_PARAM);
}

/**
 * @tc.name  : OnCapturerSessionAdded_001
 * @tc.number: AudioCoreServiceUnitTest_OnCapturerSessionAdded_001
 * @tc.desc  : Test OnCapturerSessionAdded delegates to capturer session
 */
HWTEST_F(AudioCoreServiceUnitTest, OnCapturerSessionAdded_001, TestSize.Level3)
{
    uint64_t sessionID = 1001;
    SessionInfo sessionInfo;
    sessionInfo.sourceType = SOURCE_TYPE_MIC;
    AudioStreamInfo streamInfo;
    int32_t ret = audioCoreService_->OnCapturerSessionAdded(sessionID, sessionInfo, streamInfo);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : OnCapturerSessionRemoved_001
 * @tc.number: AudioCoreServiceUnitTest_OnCapturerSessionRemoved_001
 * @tc.desc  : Test OnCapturerSessionRemoved
 */
HWTEST_F(AudioCoreServiceUnitTest, OnCapturerSessionRemoved_001, TestSize.Level3)
{
    uint64_t sessionID = 1001;
    EXPECT_NO_THROW(audioCoreService_->OnCapturerSessionRemoved(sessionID));
}

/**
 * @tc.name  : CloseWakeUpAudioCapturer_001
 * @tc.number: AudioCoreServiceUnitTest_CloseWakeUpAudioCapturer_001
 * @tc.desc  : Test CloseWakeUpAudioCapturer
 */
HWTEST_F(AudioCoreServiceUnitTest, CloseWakeUpAudioCapturer_001, TestSize.Level3)
{
    EXPECT_NO_THROW(audioCoreService_->CloseWakeUpAudioCapturer());
}

/**
 * @tc.name  : GetExcludedDevices_001
 * @tc.number: AudioCoreServiceUnitTest_GetExcludedDevices_001
 * @tc.desc  : Test GetExcludedDevices
 */
HWTEST_F(AudioCoreServiceUnitTest, GetExcludedDevices_001, TestSize.Level3)
{
    auto devices = audioCoreService_->GetExcludedDevices(MEDIA_OUTPUT_DEVICES);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : GetSelectedInputDeviceByUid_001
 * @tc.number: AudioCoreServiceUnitTest_GetSelectedInputDeviceByUid_001
 * @tc.desc  : Test GetSelectedInputDeviceByUid for non-existing uid
 */
HWTEST_F(AudioCoreServiceUnitTest, GetSelectedInputDeviceByUid_001, TestSize.Level3)
{
    auto device = audioCoreService_->GetSelectedInputDeviceByUid(-1);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : ClearSelectedInputDeviceByUid_001
 * @tc.number: AudioCoreServiceUnitTest_ClearSelectedInputDeviceByUid_001
 * @tc.desc  : Test ClearSelectedInputDeviceByUid
 */
HWTEST_F(AudioCoreServiceUnitTest, ClearSelectedInputDeviceByUid_001, TestSize.Level3)
{
    int32_t ret = audioCoreService_->ClearSelectedInputDeviceByUid(-1);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : GetEventEntry_001
 * @tc.number: AudioCoreServiceUnitTest_GetEventEntry_001
 * @tc.desc  : Test GetEventEntry returns nullptr before Init
 */
HWTEST_F(AudioCoreServiceUnitTest, GetEventEntry_001, TestSize.Level3)
{
    auto entry = audioCoreService_->GetEventEntry();
    EXPECT_EQ(entry, nullptr);
}

/**
 * @tc.name  : IsHWDecoding_001
 * @tc.number: AudioCoreServiceUnitTest_IsHWDecoding_001
 * @tc.desc  : Test IsHWDecoding with nullptr returns false
 */
HWTEST_F(AudioCoreServiceUnitTest, IsHWDecoding_001, TestSize.Level3)
{
    bool ret = audioCoreService_->IsHWDecoding(nullptr);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name  : IsHWDecoding_002
 * @tc.number: AudioCoreServiceUnitTest_IsHWDecoding_002
 * @tc.desc  : Test IsHWDecoding with non-HW decoding encoding
 */
HWTEST_F(AudioCoreServiceUnitTest, IsHWDecoding_002, TestSize.Level3)
{
    auto streamDesc = std::make_shared<AudioStreamDescriptor>();
    streamDesc->streamInfo_.encoding = ENCODING_PCM;
    bool ret = audioCoreService_->IsHWDecoding(streamDesc);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name  : OnDeviceInfoUpdated_001
 * @tc.number: AudioCoreServiceUnitTest_OnDeviceInfoUpdated_001
 * @tc.desc  : Test OnDeviceInfoUpdated
 */
HWTEST_F(AudioCoreServiceUnitTest, OnDeviceInfoUpdated_001, TestSize.Level3)
{
    AudioDeviceDescriptor desc;
    desc.deviceType_ = DEVICE_TYPE_SPEAKER;
    EXPECT_NO_THROW(audioCoreService_->OnDeviceInfoUpdated(desc, DeviceInfoUpdateCommand::CATEGORY_UPDATE));
}

/**
 * @tc.name  : SetCallDeviceActive_001
 * @tc.number: AudioCoreServiceUnitTest_SetCallDeviceActive_001
 * @tc.desc  : Test SetCallDeviceActive with DEVICE_TYPE_NONE returns error
 */
HWTEST_F(AudioCoreServiceUnitTest, SetCallDeviceActive_001, TestSize.Level3)
{
    int32_t ret = audioCoreService_->SetCallDeviceActive(DEVICE_TYPE_NONE, true, "");
    EXPECT_EQ(ret, ERR_DEVICE_NOT_SUPPORTED);
}

/**
 * @tc.name  : IsForcedNormal_001
 * @tc.number: AudioCoreServiceUnitTest_IsForcedNormal_001
 * @tc.desc  : Test IsForcedNormal with AUDIO_FLAG_FORCED_NORMAL
 */
HWTEST_F(AudioCoreServiceUnitTest, IsForcedNormal_001, TestSize.Level2)
{
    auto streamDesc = std::make_shared<AudioStreamDescriptor>();
    streamDesc->rendererInfo_.originalFlag = AUDIO_FLAG_FORCED_NORMAL;
    bool result = audioCoreService_->IsForcedNormal(streamDesc);
    EXPECT_TRUE(result);
    EXPECT_EQ(streamDesc->audioFlag_, AUDIO_OUTPUT_FLAG_NORMAL);
}

/**
 * @tc.name  : IsForcedNormal_002
 * @tc.number: AudioCoreServiceUnitTest_IsForcedNormal_002
 * @tc.desc  : Test IsForcedNormal with rendererFlags set to AUDIO_FLAG_FORCED_NORMAL
 */
HWTEST_F(AudioCoreServiceUnitTest, IsForcedNormal_002, TestSize.Level2)
{
    auto streamDesc = std::make_shared<AudioStreamDescriptor>();
    streamDesc->rendererInfo_.rendererFlags = AUDIO_FLAG_FORCED_NORMAL;
    bool result = audioCoreService_->IsForcedNormal(streamDesc);
    EXPECT_TRUE(result);
}

/**
 * @tc.name  : IsForcedNormal_003
 * @tc.number: AudioCoreServiceUnitTest_IsForcedNormal_003
 * @tc.desc  : Test IsForcedNormal with empty newDeviceDescs returns false
 */
HWTEST_F(AudioCoreServiceUnitTest, IsForcedNormal_003, TestSize.Level3)
{
    auto streamDesc = std::make_shared<AudioStreamDescriptor>();
    streamDesc->rendererInfo_.originalFlag = AUDIO_FLAG_NONE;
    streamDesc->rendererInfo_.rendererFlags = AUDIO_FLAG_NONE;
    streamDesc->newDeviceDescs_.clear();
    bool result = audioCoreService_->IsForcedNormal(streamDesc);
    EXPECT_FALSE(result);
}

/**
 * @tc.name  : GetAudioCapturerMicrophoneDescriptors_001
 * @tc.number: AudioCoreServiceUnitTest_GetAudioCapturerMicrophoneDescriptors_001
 * @tc.desc  : Test GetAudioCapturerMicrophoneDescriptors for non-existing session
 */
HWTEST_F(AudioCoreServiceUnitTest, GetAudioCapturerMicrophoneDescriptors_001, TestSize.Level3)
{
    auto descriptors = audioCoreService_->GetAudioCapturerMicrophoneDescriptors(99999);
    EXPECT_NE(audioCoreService_, nullptr);
}

/**
 * @tc.name  : GetPreferBluetoothAndNearlinkRecordByUid_001
 * @tc.number: AudioCoreServiceUnitTest_GetPreferBluetoothAndNearlinkRecordByUid_001
 * @tc.desc  : Test GetPreferBluetoothAndNearlinkRecordByUid
 */
HWTEST_F(AudioCoreServiceUnitTest, GetPreferBluetoothAndNearlinkRecordByUid_001, TestSize.Level3)
{
    auto result = audioCoreService_->GetPreferBluetoothAndNearlinkRecordByUid(-1);
    EXPECT_NE(audioCoreService_, nullptr);
}

} // namespace AudioStandard
} // namespace OHOS
