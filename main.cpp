#include "Disk_File.h"
int main()
{
        string m1="213251245324124532412453241245324124532412453241245324124532412453241245324124532412453241245324124532412453241245324124532412453241245324124532412453241245324";
        
        Disk_File file=Disk_File("malcolm.bin", 0.1);
        Disk_File file2=Disk_File("lala", 0.1);
        file2.writeHeader(m1);
        file.writeHeader(m1);
        file2.write(m1, 1, 3);
        file.write(m1, 0, 0);
        cout <<file.read(0, 0, sizeof(m1))<<endl;
        cout <<file.readHeader() <<endl;
        cout <<file2.read(1, 3, sizeof(m1))<<endl;
        cout <<file2.readHeader() <<endl;
        
}