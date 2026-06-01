# Key-Value Store Projesi

## Setup

Projeyi derlemek için:

```bash
make
```

## Çalıştırma

### Terminal 1 (Server)

```bash
./server
```

### Terminal 2 (Client)

```bash
./client
```

## Client Komutları

Client üzerinden aşağıdaki komutlar kullanılabilir:

### SET

Bir anahtar-değer çifti ekler veya günceller.

```bash
SET <key> <value>
```

### GET

Verilen anahtarın değerini getirir.

```bash
GET <key>
```

### DELETE

Verilen anahtarı siler.

```bash
DELETE <key>
```

### LIST

Tüm kayıtları listeler.

```bash
LIST
```

## Örnek Kullanım

```bash
SET name Baris
GET name
DELETE name
LIST
```

## Notlar

* Server çalışmadan client başlatılmamalıdır.
* Key-value verileri RAM üzerinde tutulur.
* Program kapatıldığında veriler silinir.
