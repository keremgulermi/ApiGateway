# RFC 9213 Uyumlu API Gateway İstek Zamanlayıcısı 🚀

Bu proje, Kırklareli Üniversitesi (KLU) Yazılım Mühendisliği bölümü kapsamında geliştirilmiş, yüksek trafikli ağ geçitlerinde (API Gateway) gelen HTTP isteklerini **RFC 9213** standardına göre önceliklendiren bir **Priority Queue (Öncelikli Kuyruk)** simülasyonudur.

Sistem, sıradan linear diziler yerine **Min-Heap** algoritması kullanılarak optimize edilmiş ve C dilinin sunduğu dinamik bellek yönetimi (malloc/realloc/free) prensipleriyle inşa edilmiştir.

## 🛠️ Teknik Özellikler

* **RFC 9213 Ayrıştırıcı (Parser):** Gelen HTTP header string'lerini (ör. `u=2, i`) standartlara uygun olarak parse eder ve `urgency` ile `incremental` değerlerini ayrıştırır.
* **Min-Heap Algoritması:** İsteklerin kuyruğa eklenmesi (Heapify-Up) ve kuyruktan çıkarılması (Heapify-Down) işlemlerini **O(log n)** zaman karmaşıklığında gerçekleştirerek darboğazları engeller.
* **Dinamik Bellek Yönetimi:** Kuyruk boyutu statik bırakılmamıştır. Gelen istek sayısı kapasiteyi aştığında, `realloc` ile bellek otomatik olarak 2 katına çıkarılır. İşlem bitiminde sıfır bellek sızıntısı (0 Memory Leak) ile tüm kaynaklar sisteme iade edilir.
* **Modüler Mimari (Separation of Concerns):** Proje; ayrıştırma, algoritma ve uygulama katmanları olmak üzere bağımsız modüllere bölünmüştür.

## 📂 Proje Mimarisi

Proje 3 ana modülden oluşmaktadır:

1. `rfc9213_parser.h` & `rfc9213_parser.c`: Gelen string veriyi anlamlandıran ve bir C yapısına (Struct) dönüştüren bağımsız katman.
2. `min_heap.h` & `min_heap.c`: Sadece veri yapısı ve ağaç mantığını barındıran, verinin ne olduğuyla ilgilenmeyen algoritmik katman.
3. `main.c`: Sistemi başlatan, API isteklerini simüle eden ve parçaları bir araya getiren uygulama katmanı.

## 💻 Kurulum ve Çalıştırma

Projeyi yerel ortamınızda derlemek ve çalıştırmak için sisteminizde GCC derleyicisinin kurulu olması gerekmektedir.
