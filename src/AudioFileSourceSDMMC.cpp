#include "AudioFileSourceSDMMC.h"

AudioFileSourceSDMMC::AudioFileSourceSDMMC(const char* filename, SDCard* sdCard) {
  sd = sdCard;
  open(filename);
}

bool AudioFileSourceSDMMC::open(const char* filename) {
  if (!sd->isInitialized()) return false;
  file = SD_MMC.open(filename);
  return file ? true : false;
}

uint32_t AudioFileSourceSDMMC::read(void *data, uint32_t len) {
  return file.read((uint8_t*)data, len);
}

bool AudioFileSourceSDMMC::seek(int32_t pos, int dir) {
  if (dir == SEEK_SET) return file.seek(pos);
  if (dir == SEEK_CUR) return file.seek(file.position() + pos);
  if (dir == SEEK_END) return file.seek(file.size() + pos);
  return false;
}

bool AudioFileSourceSDMMC::close() {
  file.close();
  return true;
}

bool AudioFileSourceSDMMC::isOpen() {
  return file ? true : false;
}

uint32_t AudioFileSourceSDMMC::getSize() {
  return file.size();
}

uint32_t AudioFileSourceSDMMC::getPos() {
  return file.position();
}