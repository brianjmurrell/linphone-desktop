/*
 * SettingsModel.cpp
 * Copyright (C) 2017  Belledonne Communications, Grenoble, France
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *  Created on: February 2, 2017
 *      Author: Ronan Abhamon
 */

#include <QDir>

#include "../../app/paths/Paths.hpp"
#include "../../utils.hpp"
#include "../core/CoreManager.hpp"

#include "SettingsModel.hpp"

using namespace std;

// =============================================================================

const string SettingsModel::UI_SECTION("ui");

SettingsModel::SettingsModel (QObject *parent) : QObject(parent) {
  m_config = CoreManager::getInstance()->getCore()->getConfig();
}

// =============================================================================
// Audio.
// =============================================================================

QVariantList SettingsModel::getAudioCodecs () const {
  QVariantList list;

  // for (const auto &codec : CoreManager::getInstance()->getCore()->getAudioCodecs()) {
  // QVariantMap map;
  //
  // map["mime"] = ::Utils::linphoneStringToQString(codec->getMimeType());
  // map["channels"] = codec->getChannels();
  // map["bitrate"] = codec->getNormalBitrate();
  // map["type"] = codec->getType();
  // map["isVbr"] = codec->isVbr();
  //
  // list << map;
  // }

  return list;
}

void SettingsModel::setAudioCodecs (const QVariantList &codecs) {
  // TODO
  emit audioCodecsChanged(codecs);
}

// -----------------------------------------------------------------------------

QStringList SettingsModel::getAudioDevices () const {
  QStringList list;

  for (const auto &device : CoreManager::getInstance()->getCore()->getSoundDevices())
    list << ::Utils::linphoneStringToQString(device);

  return list;
}

// -----------------------------------------------------------------------------

QString SettingsModel::getCaptureDevice () const {
  return ::Utils::linphoneStringToQString(
    CoreManager::getInstance()->getCore()->getCaptureDevice()
  );
}

void SettingsModel::setCaptureDevice (const QString &device) {
  CoreManager::getInstance()->getCore()->setCaptureDevice(
    ::Utils::qStringToLinphoneString(device)
  );
  emit captureDeviceChanged(device);
}

// -----------------------------------------------------------------------------

QString SettingsModel::getPlaybackDevice () const {
  return ::Utils::linphoneStringToQString(
    CoreManager::getInstance()->getCore()->getPlaybackDevice()
  );
}

void SettingsModel::setPlaybackDevice (const QString &device) {
  CoreManager::getInstance()->getCore()->setPlaybackDevice(
    ::Utils::qStringToLinphoneString(device)
  );
  emit playbackDeviceChanged(device);
}

// -----------------------------------------------------------------------------

QString SettingsModel::getRingerDevice () const {
  return ::Utils::linphoneStringToQString(
    CoreManager::getInstance()->getCore()->getRingerDevice()
  );
}

void SettingsModel::setRingerDevice (const QString &device) {
  CoreManager::getInstance()->getCore()->setRingerDevice(
    ::Utils::qStringToLinphoneString(device)
  );
  emit ringerDeviceChanged(device);
}

// -----------------------------------------------------------------------------

QString SettingsModel::getRingPath () const {
  return ::Utils::linphoneStringToQString(CoreManager::getInstance()->getCore()->getRing());
}

void SettingsModel::setRingPath (const QString &path) {
  QString cleaned_path = QDir::cleanPath(path);

  CoreManager::getInstance()->getCore()->setRing(
    ::Utils::qStringToLinphoneString(cleaned_path)
  );

  emit ringPathChanged(cleaned_path);
}

// -----------------------------------------------------------------------------

bool SettingsModel::getEchoCancellationEnabled () const {
  return CoreManager::getInstance()->getCore()->echoCancellationEnabled();
}

void SettingsModel::setEchoCancellationEnabled (bool status) {
  CoreManager::getInstance()->getCore()->enableEchoCancellation(status);
  emit echoCancellationEnabledChanged(status);
}

// =============================================================================
// Video.
// =============================================================================

QStringList SettingsModel::getVideoDevices () const {
  QStringList list;

  for (const auto &device : CoreManager::getInstance()->getCore()->getVideoDevices())
    list << ::Utils::linphoneStringToQString(device);

  return list;
}

// -----------------------------------------------------------------------------

QString SettingsModel::getVideoDevice () const {
  return ::Utils::linphoneStringToQString(
    CoreManager::getInstance()->getCore()->getVideoDevice()
  );
}

void SettingsModel::setVideoDevice (const QString &device) {
  CoreManager::getInstance()->getCore()->setVideoDevice(
    ::Utils::qStringToLinphoneString(device)
  );
  emit videoDeviceChanged(device);
}

// -----------------------------------------------------------------------------

QString SettingsModel::getVideoPreset () const {
  return ::Utils::linphoneStringToQString(
    CoreManager::getInstance()->getCore()->getVideoPreset()
  );
}

void SettingsModel::setVideoPreset (const QString &preset) {
  CoreManager::getInstance()->getCore()->setVideoPreset(
    ::Utils::qStringToLinphoneString(preset)
  );
  emit videoPresetChanged(preset);
}

// -----------------------------------------------------------------------------

int SettingsModel::getVideoFramerate () const {
  return static_cast<int>(CoreManager::getInstance()->getCore()->getPreferredFramerate());
}

void SettingsModel::setVideoFramerate (int framerate) {
  CoreManager::getInstance()->getCore()->setPreferredFramerate(static_cast<float>(framerate));
  emit videoFramerateChanged(framerate);
}

// =============================================================================
// Chat & calls.
// =============================================================================

int SettingsModel::getAutoAnswerDelay () const {
  return m_config->getInt(UI_SECTION, "auto_answer_delay", 0);
}

void SettingsModel::setAutoAnswerDelay (int delay) {
  m_config->setInt(UI_SECTION, "auto_answer_delay", delay);
  emit autoAnswerDelayChanged(delay);
}

// -----------------------------------------------------------------------------

bool SettingsModel::getAutoAnswerStatus () const {
  return !!m_config->getInt(UI_SECTION, "auto_answer", 0);
}

void SettingsModel::setAutoAnswerStatus (bool status) {
  m_config->setInt(UI_SECTION, "auto_answer", status);
  emit autoAnswerStatusChanged(status);
}

// -----------------------------------------------------------------------------

QString SettingsModel::getFileTransferUrl () const {
  return ::Utils::linphoneStringToQString(
    CoreManager::getInstance()->getCore()->getFileTransferServer()
  );
}

void SettingsModel::setFileTransferUrl (const QString &url) {
  CoreManager::getInstance()->getCore()->setFileTransferServer(
    ::Utils::qStringToLinphoneString(url)
  );
  emit fileTransferUrlChanged(url);
}

// -----------------------------------------------------------------------------

bool SettingsModel::getLimeIsSupported () const {
  return CoreManager::getInstance()->getCore()->limeAvailable();
}

// -----------------------------------------------------------------------------

inline QVariant buildEncryptionDescription (SettingsModel::MediaEncryption encryption, const char *description) {
  return QVariantList() << encryption << description;
}

QVariantList SettingsModel::getSupportedMediaEncryptions () const {
  shared_ptr<linphone::Core> core = CoreManager::getInstance()->getCore();
  QVariantList list;

  if (core->mediaEncryptionSupported(linphone::MediaEncryptionDTLS))
    list << buildEncryptionDescription(MediaEncryptionDtls, "DTLS");

  if (core->mediaEncryptionSupported(linphone::MediaEncryptionSRTP))
    list << buildEncryptionDescription(MediaEncryptionSrtp, "SRTP");

  if (core->mediaEncryptionSupported(linphone::MediaEncryptionZRTP))
    list << buildEncryptionDescription(MediaEncryptionZrtp, "ZRTP");

  return list;
}

// -----------------------------------------------------------------------------

SettingsModel::MediaEncryption SettingsModel::getMediaEncryption () const {
  return static_cast<SettingsModel::MediaEncryption>(
    CoreManager::getInstance()->getCore()->getMediaEncryption()
  );
}

void SettingsModel::setMediaEncryption (MediaEncryption encryption) {
  if (encryption == getMediaEncryption())
    return;

  if (encryption != SettingsModel::MediaEncryptionZrtp)
    setLimeState(SettingsModel::LimeStateDisabled);

  CoreManager::getInstance()->getCore()->setMediaEncryption(
    static_cast<linphone::MediaEncryption>(encryption)
  );

  emit mediaEncryptionChanged(encryption);
}

// -----------------------------------------------------------------------------

SettingsModel::LimeState SettingsModel::getLimeState () const {
  return static_cast<SettingsModel::LimeState>(
    CoreManager::getInstance()->getCore()->limeEnabled()
  );
}

void SettingsModel::setLimeState (LimeState state) {
  if (state == getLimeState())
    return;

  if (state != SettingsModel::LimeStateDisabled)
    setMediaEncryption(SettingsModel::MediaEncryptionZrtp);

  CoreManager::getInstance()->getCore()->enableLime(
    static_cast<linphone::LimeState>(state)
  );

  emit limeStateChanged(state);
}

// =============================================================================
// Network.
// =============================================================================

bool SettingsModel::getUseSipInfoForDtmfs () const {
  return CoreManager::getInstance()->getCore()->getUseInfoForDtmf();
}

void SettingsModel::setUseSipInfoForDtmfs (bool status) {
  shared_ptr<linphone::Core> core = CoreManager::getInstance()->getCore();

  if (status) {
    core->setUseRfc2833ForDtmf(false);
    core->setUseInfoForDtmf(true);
  } else {
    core->setUseInfoForDtmf(false);
    core->setUseRfc2833ForDtmf(true);
  }

  emit dtmfsProtocolChanged();
}

// -----------------------------------------------------------------------------

bool SettingsModel::getUseRfc2833ForDtmfs () const {
  return CoreManager::getInstance()->getCore()->getUseRfc2833ForDtmf();
}

void SettingsModel::setUseRfc2833ForDtmfs (bool status) {
  shared_ptr<linphone::Core> core = CoreManager::getInstance()->getCore();

  if (status) {
    core->setUseInfoForDtmf(false);
    core->setUseRfc2833ForDtmf(true);
  } else {
    core->setUseRfc2833ForDtmf(false);
    core->setUseInfoForDtmf(true);
  }

  emit dtmfsProtocolChanged();
}

// -----------------------------------------------------------------------------

bool SettingsModel::getIpv6Enabled () const {
  return CoreManager::getInstance()->getCore()->ipv6Enabled();
}

void SettingsModel::setIpv6Enabled (bool status) {
  CoreManager::getInstance()->getCore()->enableIpv6(status);
  emit ipv6EnabledChanged(status);
}

// -----------------------------------------------------------------------------

int SettingsModel::getDownloadBandwidth () const {
  return CoreManager::getInstance()->getCore()->getDownloadBandwidth();
}

void SettingsModel::setDownloadBandwidth (int bandwidth) {
  CoreManager::getInstance()->getCore()->setDownloadBandwidth(bandwidth);
  emit downloadBandWidthChanged(getDownloadBandwidth());
}

// -----------------------------------------------------------------------------

int SettingsModel::getUploadBandwidth () const {
  return CoreManager::getInstance()->getCore()->getUploadBandwidth();
}

void SettingsModel::setUploadBandwidth (int bandwidth) {
  CoreManager::getInstance()->getCore()->setUploadBandwidth(bandwidth);
  emit uploadBandWidthChanged(getUploadBandwidth());
}

// -----------------------------------------------------------------------------

bool SettingsModel::getAdaptiveRateControlEnabled () const {
  return CoreManager::getInstance()->getCore()->adaptiveRateControlEnabled();
}

void SettingsModel::setAdaptiveRateControlEnabled (bool status) {
  CoreManager::getInstance()->getCore()->enableAdaptiveRateControl(status);
  emit adaptiveRateControlEnabledChanged(status);
}

// -----------------------------------------------------------------------------

// bool SettingsModel::getTcpPortEnabled () const {}

// void SettingsModel::setTcpPortEnabled (bool status) {
// emit tcpPortEnabledChanged(status);
// }

// -----------------------------------------------------------------------------

QList<int> SettingsModel::getAudioPortRange () const {
  linphone::IntRange range = CoreManager::getInstance()->getCore()->getAudioPortRange();
  return QList<int>() << range.getMin() << range.getMax();
}

void SettingsModel::setAudioPortRange (const QList<int> &range) {
  shared_ptr<linphone::Core> core = CoreManager::getInstance()->getCore();
  int a = range[0];
  int b = range[1];

  if (b == -1)
    core->setAudioPort(a);
  else
    core->setAudioPortRange(a, b);

  emit audioPortRangeChanged(a, b);
}

// -----------------------------------------------------------------------------

QList<int> SettingsModel::getVideoPortRange () const {
  linphone::IntRange range = CoreManager::getInstance()->getCore()->getVideoPortRange();
  return QList<int>() << range.getMin() << range.getMax();
}

void SettingsModel::setVideoPortRange (const QList<int> &range) {
  shared_ptr<linphone::Core> core = CoreManager::getInstance()->getCore();
  int a = range[0];
  int b = range[1];

  if (b == -1)
    core->setVideoPort(a);
  else
    core->setVideoPortRange(a, b);

  emit videoPortRangeChanged(a, b);
}

// -----------------------------------------------------------------------------

bool SettingsModel::getIceEnabled () const {
  return CoreManager::getInstance()->getCore()->getNatPolicy()->iceEnabled();
}

void SettingsModel::setIceEnabled (bool status) {
  shared_ptr<linphone::NatPolicy> nat_policy = CoreManager::getInstance()->getCore()->getNatPolicy();

  nat_policy->enableIce(status);
  nat_policy->enableStun(status);

  emit iceEnabledChanged(status);
}

// -----------------------------------------------------------------------------

bool SettingsModel::getTurnEnabled () const {
  return CoreManager::getInstance()->getCore()->getNatPolicy()->turnEnabled();
}

void SettingsModel::setTurnEnabled (bool status) {
  CoreManager::getInstance()->getCore()->getNatPolicy()->enableTurn(status);
  emit turnEnabledChanged(status);
}

// -----------------------------------------------------------------------------

QString SettingsModel::getStunServer () const {
  return ::Utils::linphoneStringToQString(
    CoreManager::getInstance()->getCore()->getNatPolicy()->getStunServer()
  );
}

void SettingsModel::setStunServer (const QString &stun_server) {
  CoreManager::getInstance()->getCore()->getNatPolicy()->setStunServer(
    ::Utils::qStringToLinphoneString(stun_server)
  );
}

// -----------------------------------------------------------------------------

QString SettingsModel::getTurnUser () const {
  return ::Utils::linphoneStringToQString(
    CoreManager::getInstance()->getCore()->getNatPolicy()->getStunServerUsername()
  );
}

void SettingsModel::setTurnUser (const QString &user) {
  CoreManager::getInstance()->getCore()->getNatPolicy()->setStunServerUsername(
    ::Utils::qStringToLinphoneString(user)
  );

  emit turnUserChanged(user);
}

// -----------------------------------------------------------------------------

QString SettingsModel::getTurnPassword () const {
  shared_ptr<linphone::Core> core = CoreManager::getInstance()->getCore();
  shared_ptr<linphone::NatPolicy> nat_policy = core->getNatPolicy();
  shared_ptr<const linphone::AuthInfo> auth_info = core->findAuthInfo(nat_policy->getStunServerUsername(), "", "");

  return auth_info ? ::Utils::linphoneStringToQString(auth_info->getPasswd()) : "";
}

void SettingsModel::setTurnPassword (const QString &password) {
  shared_ptr<linphone::Core> core = CoreManager::getInstance()->getCore();
  shared_ptr<linphone::NatPolicy> nat_policy = core->getNatPolicy();

  const string &username = nat_policy->getStunServerUsername();
  shared_ptr<const linphone::AuthInfo> auth_info = core->findAuthInfo(username, "", "");

  if (auth_info) {
    shared_ptr<linphone::AuthInfo> auth_info_clone = auth_info->clone();
    auth_info_clone->setPasswd(::Utils::qStringToLinphoneString(password));

    core->removeAuthInfo(auth_info);
    core->addAuthInfo(auth_info_clone);
  } else {
    auth_info = linphone::Factory::get()->createAuthInfo(username, username, ::Utils::qStringToLinphoneString(password), "", "", "");
    core->addAuthInfo(auth_info);
  }

  emit turnPasswordChanged(password);
}

// -----------------------------------------------------------------------------

int SettingsModel::getDscpSip () const {
  return CoreManager::getInstance()->getCore()->getSipDscp();
}

void SettingsModel::setDscpSip (int dscp) {
  CoreManager::getInstance()->getCore()->setSipDscp(dscp);
  emit dscpSipChanged(dscp);
}

int SettingsModel::getDscpAudio () const {
  return CoreManager::getInstance()->getCore()->getAudioDscp();
}

void SettingsModel::setDscpAudio (int dscp) {
  CoreManager::getInstance()->getCore()->setAudioDscp(dscp);
  emit dscpAudioChanged(dscp);
}

int SettingsModel::getDscpVideo () const {
  return CoreManager::getInstance()->getCore()->getVideoDscp();
}

void SettingsModel::setDscpVideo (int dscp) {
  CoreManager::getInstance()->getCore()->setVideoDscp(dscp);
  emit dscpVideoChanged(dscp);
}

// =============================================================================
// Misc.
// =============================================================================

QString SettingsModel::getSavedScreenshotsFolder () const {
  return QDir::cleanPath(
    ::Utils::linphoneStringToQString(
      m_config->getString(UI_SECTION, "saved_screenshots_folder", Paths::getCapturesDirpath())
    )
  ) + QDir::separator();
}

void SettingsModel::setSavedScreenshotsFolder (const QString &folder) {
  QString cleaned_folder = QDir::cleanPath(folder) + QDir::separator();

  m_config->setString(UI_SECTION, "saved_screenshots_folder", ::Utils::qStringToLinphoneString(cleaned_folder));
  emit savedScreenshotsFolderChanged(cleaned_folder);
}

// -----------------------------------------------------------------------------

QString SettingsModel::getSavedVideosFolder () const {
  return QDir::cleanPath(
    ::Utils::linphoneStringToQString(
      m_config->getString(UI_SECTION, "saved_videos_folder", Paths::getCapturesDirpath())
    )
  ) + QDir::separator();
}

void SettingsModel::setSavedVideosFolder (const QString &folder) {
  QString _folder = QDir::cleanPath(folder) + QDir::separator();

  m_config->setString(UI_SECTION, "saved_videos_folder", ::Utils::qStringToLinphoneString(_folder));
  emit savedVideosFolderChanged(_folder);
}
