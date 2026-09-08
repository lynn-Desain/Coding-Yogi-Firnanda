class mahasiswa:
    def __init__(self, nama, nim, jurusan):
        self.nama = nama
        self.nim = nim
        self.jurusan = jurusan

    def tampilkan_data(self):
        print("Nama:", self.nama)  
        print("NIM:", self.nim)
        print("Jurusan:", self.jurusan)

    def perkenalan(self):
        print(f"Halo, nama saya {self.nama} dari jurusan {self.jurusan}.")   

mhs1 = mahasiswa("Yogi Firnanda Saputra", "2511102441170", "Teknik Informatika")
mhs2 = mahasiswa("Abdul Zaky", "2511102441729", "Teknik Sipil")
mhs3 = mahasiswa("Nazril", "25111024411321", "Teknik Informatika")

mhs1.tampilkan_data()
mhs2.tampilkan_data()
mhs3.tampilkan_data()

mhs1.perkenalan()
mhs2.perkenalan()
mhs3.perkenalan()