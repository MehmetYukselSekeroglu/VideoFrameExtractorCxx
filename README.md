# Video Frame Extractor Pro

[![Version](https://img.shields.io/badge/Version-1.0--stable-brightgreen)](https://github.com/MehmetYukselSekeroglu/VideoFrameExtractorCxx/releases)
[![License](https://img.shields.io/badge/License-MIT-blue)](https://github.com/MehmetYukselSekeroglu/VideoFrameExtractorCxx?tab=MIT-1-ov-file)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)](https://github.com/MehmetYukselSekeroglu/VideoFrameExtractorCxx)
[![Qt](https://img.shields.io/badge/Qt-6.9.3-green)](https://www.qt.io/)
[![OpenCV](https://img.shields.io/badge/OpenCV-4.12.0-orange)](https://opencv.org/)

**Video Frame Extractor Pro**, videoları yüksek kalitede bireysel karelere (frame) ayırmak için geliştirilmiş profesyonel bir masaüstü uygulamasıdır. Qt framework ve OpenCV kütüphanesi kullanılarak C++ ile yazılmıştır.

## ✨ Özellikler

### 🚀 Temel İşlevler
- **Çoklu Format Desteği**: MP4, AVI, MOV, MKV, WMV, FLV, MPEG ve daha fazlası
- **Yüksek Performans**: OpenCV optimizasyonu ile hızlı kare ayrıştırma
- **Çoklu İş Parçacığı**: QThread kullanımı ile arayüz donması olmadan işlem
- **Gerçek Zamanlı İlerleme**: Canlı progress takibi ve detaylı loglama

### 🎨 Kullanıcı Arayüzü
- **Modern Tasarım**: Profesyonel koyu tema arayüz
- **Sezgisel Kontroller**: Kolay kullanım için optimize edilmiş düzen
- **Zengin Görsel Geribildirim**: Emoji ikonları ve renk kodlaması
- **Türkçe Dil Desteği**: Yerelleştirilmiş arayüz

### ⚡ Gelişmiş Özellikler
- **Durdur/Devam Et**: İşlem sırasında durdurma ve devam ettirme
- **Otomatik Klasör Yönetimi**: Akıllı çıktı dizini organizasyonu
- **Performans Metrikleri**: İşlem hızı ve süre takibi
- **Detaylı Loglama**: Tarih/saat bilgili kapsamlı log sistemi

## 📥 İndirme ve Kurulum

### Windows Kurulumu
1. **[Son Sürümü İndir](https://github.com/MehmetYukselSekeroglu/VideoFrameExtractorCxx/releases/latest)**
2. `VideoFrameExtractorPro_Setup.exe` dosyasını çalıştırın
3. Kurulum sihirbazını takip edin
4. Masaüstü kısayolundan uygulamayı başlatın

### Sistem Gereksinimleri
- **İşletim Sistemi**: Windows 10/11 (64-bit)
- **İşlemci**: Intel i3 veya eşdeğeri
- **RAM**: Minimum 4GB (8GB önerilir)
- **Depolama**: 500MB boş alan
- **Runtime**: Visual C++ Redistributable

## 🎮 Kullanım Kılavuzu

### Hızlı Başlangıç
1. **Video Seç** butonu ile hedef video dosyasını belirleyin
2. **Çıktı Dizini** seçin (varsayılan: `output_videoname`)
3. **Ayrıştırmayı Başlat** butonu ile süreci başlatın
4. İlerlemeyi gerçek zamanlı progress bar ve loglardan takip edin

### Çıktı Formatı
- **Dosya Adlandırma**: `frame_00001.jpg`, `frame_00002.jpg`, ...
- **Görüntü Kalitesi**: %95 JPEG kalitesi
- **Renk Formatı**: Orijinal video renk formatı korunur
- **Sıralı Numaralandırma**: 5 haneli sıralı dosya isimlendirme

## 🛠️ Geliştirici için

### Derleme Gereksinimleri
- **Qt**: 6.9.3 veya üzeri
- **OpenCV**: 4.12.0 veya üzeri
- **CMake**: 3.16 veya üzeri
- **C++ Derleyici**: MSVC 2022, GCC veya Clang

### Kaynak Koddan Derleme
```bash
# Repoyu klonla
git clone https://github.com/MehmetYukselSekeroglu/VideoFrameExtractorCxx.git
cd VideoFrameExtractorCxx

# Build dizini oluştur
mkdir build
cd build

# CMake ile yapılandır
cmake -G "Visual Studio 17 2022" -A x64 ..

# Derle
cmake --build . --config Release