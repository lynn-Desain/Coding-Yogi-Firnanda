# latihan
class Queue:
    def __init__(self):
        self.queue = {}

    def enqueue(self, nomor, nama):
        self.queue[nomor] = nama
        print("Nomor antrian", nomor, "ditambahkan untuk", nama)

    def dequeue(self):
        if len(self.queue) == 0:
            print("Antrian kosong")
        else:
            nomor = list(self.queue.keys())[0]
            nama = self.queue[nomor]
            del self.queue[nomor]
            print("Nomor antrian", nomor, "-", nama, "dipanggil")

    def tampilkan(self):
        if len(self.queue) == 0:
            print("Tidak ada antrian")
        else:
            print("Daftar Antrian:")
            for nomor, nama in self.queue.items():
                print("Nomor:", nomor, "| Nama:", nama)


antrian = Queue() 

while True:
    print("\n=== SISTEM ANTRIAN MAHASISWA ===")
    print("1. Tambah Antrian")
    print("2. Panggil Antrian")
    print("3. Tampilkan Antrian")
    print("4. Keluar")

    pilihan = int(input("Pilih menu: "))

    if pilihan == 1:
        nomor = input("Masukkan nomor antrian: ")
        nama = input("Masukkan nama mahasiswa: ")
        antrian.enqueue(nomor, nama)

    elif pilihan == 2:
        antrian.dequeue()

    elif pilihan == 3:
        antrian.tampilkan()

    elif pilihan == 4:
        print("Program selesai")
        break

    else:
        print("Pilihan tidak tersedia")