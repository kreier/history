# Basics

This folder contains just the first steps to learn the basics about python programming.

- Hello World!
- Prime numbers until 1000

It is a easy way to try some code directly in Mu on the raspberry or Jupyter notebook in Anaconda, colaboratory or Kaggle. I tried this one:

```
import math
import time

last = 10000

start = time.time()
print("Prime numbers to 10000")

print('2, 3, 5, 7',end='')
for number in range(11, last, 2):
    prime = 1
    for divider in range(2, int(math.sqrt(number))+1, 1):
        if number/divider == int(number/divider):
            prime = 0

    if prime == 1:
        print(',', number,end='')
        
end = time.time()
print('\nThis took:', int((end - start) * 1000), 'ms.')
```

on my new Raspberry Pi 4 and it took only 326 ms.

On the console again: `python3 prime10000.py` ended after 379 ms. And 349 ms.

## Mandelbrot

Found this one for micropython simulation in a browser. Took less than a second in colab.research.google.com and now the esp32 has to show. The code:

```
minX = -2.0
maxX = 1.0
width = 60
height = 28
aspectRatio = 2

chars = ' .,-:;i+hHM$*#@ '

yScale = (maxX-minX)*(float(height)/width)*aspectRatio

for y in range(height):
    line = ''
    for x in range(width):
        c = complex(minX+x*(maxX-minX)/width, y*yScale/height-yScale/2)
        z = c
        for char in chars:
            if abs(z) > 2:
                break
            z = z*z+c
        line += char
    print(line)
```

And the result:

```
            ................................................
          ...............,,,,,,,,,,,........................
        ..........,,,,,,,,,,,,,,,,,,,,,,,,,.................
       .......,,,,,,,,,,,,,,,,-----: +::---,,,,.............
      .....,,,,,,,,,,,,,,,,------::;iMhM :----,,,,..........
     ...,,,,,,,,,,,,,,,,-------:::;+h  M+;::----,,,,,.......
    ..,,,,,,,,,,,,,,,,-------::;;i+#     +;::::--,,,,,,.....
   ..,,,,,,,,,,,,,,------::;i++++hH#    *Hh+;;; :--,,,,,....
  ..,,,,,,,,,,,,,----::::;;i$               $#@ @:-,,,,,,...
  .,,,,,,,,,,,--:::::::;;;+#$                   i;:-,,,,,,..
 .,,,,,,,---::i$iiiiiiiii+M                     h :--,,,,,,.
 ,,,------:::;iH  $* *MhhM                      @+;--,,,,,,,
 ,------::::;i+M        @                        i:---,,,,,,
 -----;;;;i+$*#                                 +;:---,,,,,,
                                              $+i;:---,,,,,,
 -----;;;;i+$*#                                 +;:---,,,,,,
 ,------::::;i+M        @                        i:---,,,,,,
 ,,,------:::;iH  $* *MhhM                      @+;--,,,,,,,
 .,,,,,,,---::i$iiiiiiiii+M                     h :--,,,,,,.
  .,,,,,,,,,,,--:::::::;;;+#$                   i;:-,,,,,,..
  ..,,,,,,,,,,,,,----::::;;i$               $#@ @:-,,,,,,...
   ..,,,,,,,,,,,,,,------::;i++++hH#    *Hh+;;; :--,,,,,....
    ..,,,,,,,,,,,,,,,,-------::;;i+#     +;::::--,,,,,,.....
     ...,,,,,,,,,,,,,,,,-------:::;+h  M+;::----,,,,,.......
      .....,,,,,,,,,,,,,,,,------::;iMhM :----,,,,..........
       .......,,,,,,,,,,,,,,,,-----: +::---,,,,.............
        ..........,,,,,,,,,,,,,,,,,,,,,,,,,.................
          ...............,,,,,,,,,,,........................
```
