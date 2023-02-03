# -*- coding: utf-8 -*-
"""
Created on Fri Oct 14 15:34:44 2022

@author: ngetc
"""

import csv
import numpy as np
import math
import matplotlib.pyplot as plt
from tabulate import tabulate

np.set_printoptions(formatter={'float': "{0:0.2e}".format})

#1
with open('transit.real.csv', newline='') as csvfile:
    temp = np.array(list(csv.reader(csvfile, delimiter=",")))

data = np.array(np.zeros((1000,2)))

for i in range(1000):
    for j in range(2):
        data[i, j] = float(temp[i, j])

plt.style.use('dark_background')
plt.rcParams["figure.figsize"] = [20, 8]
plt.rcParams["figure.autolayout"] = True

x = data[:, 0]
y = data[:, 1]

plt.xticks(np.arange(min(x), max(x)+0.05, 0.05))
plt.yticks(np.arange(min(y) + 20, max(y)+120, 100))
plt.title("Orbital Phase vs Light")
plt.scatter(x, y, marker = ".", color = "yellow")
plt.xlabel("Orbital Phase")
plt.ylabel("Light")
plt.grid()
plt.show()
print("#1: See plots")

#2
print("#2: Transit start phase = 0.4, transit end phase = 0.5")

#3
outTrans = np.array(np.zeros(901))
total1 = 0
for i in range(401):
    total1 += y[i]
    outTrans[i] = y[i]

for i in range(500, 1000):
    total1 += y[i]
    outTrans[i - 99] = y[i]

outTransFlux = total1 / 901
print("#3: Out of transit flux =", outTransFlux)

#4
outTransErr = np.std(outTrans) / math.sqrt(len(outTrans))
print("#4: Error of out of transit flux =", outTransErr)

#5
inTrans = np.array(np.zeros(99))

total2 = 0
for i in range(401, 500):
    total2 += y[i]
    inTrans[i - 401] = y[i]

inTransFlux = total2 / 99
print("#5: In transit flux =", inTransFlux)

#6
inTransErr = np.std(inTrans) / math.sqrt(len(inTrans))
print("#6: Error of in transit flux =", inTransErr)

#7
delF = outTransFlux - inTransFlux
delFErr = math.sqrt((outTransErr**2) + (inTransErr**2))
print("#7: Transit depth =", delF, ", error of transit depth =", delFErr)

#8
rho = delF / outTransFlux
rhoErr = rho * math.sqrt((delFErr / delF)**2 + (outTransErr / outTransFlux)**2)
print("#8: Fractional depth =", rho, ", error of fracional depth =", rhoErr)

#9
R_pFrac = math.sqrt(rho)
print("#9: Planet radius as fraction of star radius =", R_pFrac)

#10
R_pFracErr = R_pFrac * 1/2 * (rhoErr / rho)
print("#10: Error of planet radius as fraction =", R_pFracErr)

#11
cnv = 10**7 / 10000
h = 6.62607015 * 10**-34
k = 1.380649 * 10**-23
c = 2.99792458 * 10**8

def blackbody(nu, T):
    return cnv * (2 * h * nu**3 / c**2) * ((np.exp(h * nu / (k * T))) - 1)**-1

gFreq = (3 * 10**8) / (480 * 10**-9)
iFreq = (3 * 10**8) / (750 * 10**-9)

Bg47 = blackbody(gFreq, 4700)
Bi47 = blackbody(iFreq, 4700)
Bg49 = blackbody(gFreq, 4900)
Bi49 = blackbody(iFreq, 4900)
Bg51 = blackbody(gFreq, 5100)
Bi51 = blackbody(iFreq, 5100)
Bg53 = blackbody(gFreq, 5300)
Bi53 = blackbody(iFreq, 5300)
Bg55 = blackbody(gFreq, 5500)
Bi55 = blackbody(iFreq, 5500)

#12
sr = (695700**2 * np.pi) / (3.086*10**16)**2

fg47 = Bg47 * sr
fi47 = Bi47 * sr
fg49 = Bg49 * sr
fi49 = Bi49 * sr
fg51 = Bg51 * sr
fi51 = Bi51 * sr
fg53 = Bg53 * sr
fi53 = Bi53 * sr
fg55 = Bg55 * sr
fi55 = Bi55 * sr

#13
Jg47 = fg47 * 10**23
Ji47 = fi47 * 10**23
Jg49 = fg49 * 10**23
Ji49 = fi49 * 10**23
Jg51 = fg51 * 10**23
Ji51 = fi51 * 10**23
Jg53 = fg53 * 10**23
Ji53 = fi53 * 10**23
Jg55 = fg55 * 10**23
Ji55 = fi55 * 10**23

def magnitude(f_v):
    return -2.5 * np.log10(f_v / 3631)

mg47 = magnitude(Jg47)
mi47 = magnitude(Ji47)
mg49 = magnitude(Jg49)
mi49 = magnitude(Ji49)
mg51 = magnitude(Jg51)
mi51 = magnitude(Ji51)
mg53 = magnitude(Jg53)
mi53 = magnitude(Ji53)
mg55 = magnitude(Jg55)
mi55 = magnitude(Ji55)

#14
c47 = mg47 - mi47
c49 = mg49 - mi49
c51 = mg51 - mi51
c53 = mg53 - mi53
c55 = mg55 - mi55

tableg = np.array([
    ["B_nu", Bg47, Bg49, Bg51, Bg53, Bg55],
    ["f_v", fg47, fg49, fg51, fg53, fg55],
    ["Flux (Jy)", Jg47, Jg49, Jg51, Jg53, Jg55],
    ["m_app", mg47, mg49, mg51, mg53, mg55]
    ])

tablei = np.array([
    ["B_nu", Bi47, Bi49, Bi51, Bi53, Bi55],
    ["f_v", fi47, fi49, fi51, fi53, fi55],
    ["Flux (Jy)", Ji47, Ji49, Ji51, Ji53, Ji55],
    ["m_app", mi47, mi49, mi51, mi53, mi55]
    ])

tablec = np.array([
    ["Color (g-i)", c47, c49, c51, c53, c55],
    ])

header = (["4700K", "4900K", "5100K", "5300K", "5500K"])

print("#11, 12, 13, 14:\n")
print("g-band:")
print(tabulate(tableg, headers = header, tablefmt = "github", floatfmt='.3e'))
print("\ni-band:")
print(tabulate(tablei, headers = header, tablefmt = "github", floatfmt='.3e'))
print("\nColors:")
print(tabulate(tablec, headers = header, tablefmt = "github", floatfmt='.3f'))


#15
colors = np.array([c47, c49, c51, c53, c55])
temps = np.array([4700, 4900, 5100, 5300, 5500])

plt.style.use('default')
plt.rcParams["figure.figsize"] = [8, 5]
plt.title("Color vs Temperature")
plt.scatter(colors, temps, marker = "o", label = "Data")
plt.xlabel("g-i Color")
plt.ylabel("Temperature (K)")
plt.grid()
print("\n#15: See plots")

#16
B, A = np.polyfit(colors, temps, 1)
plt.plot(colors, B * colors + A, label = "Fit")
plt.legend()
print("#16: See plots")

#17
cStar = 16.366 - 15.5
print("#17: Star color =", cStar)

#18
cStarErr = math.sqrt(0.015**2 + 0.012**2)
print("#18: Error of star color =", cStarErr)

#19
tStar = A + cStar * B
print("#19: Star temperature =", tStar)

#20
tStarErr = abs(B) * cStarErr
print("#20: Error of star temperature =", tStarErr)

#21
fg_pre = blackbody(gFreq, tStar) * sr * 10**23
g_pre = magnitude(fg_pre)
print("#21: Predicted g-band magnitude =", g_pre)

#22
print("#22: R_star = R_sun * 10**(-(g_obs - g_pre) / 5)")

#23
R_star = 695700 * 10**(-(16.366 - g_pre) / 5)
print("#23: Star radius =", R_star)

#24
hypErr = magnitude(blackbody(gFreq, tStar + tStarErr) * sr * 10**23)
print("#24: g-band magnitude of hypothetical star =", hypErr)

#25
g_preErr = abs(hypErr - g_pre)
print("#25: Error of predicted g-band magnitude =", g_preErr)

#26
print("#26: R_starErr = math.sqrt(((-np.log(10) * R_sun /5 ) * np.exp(np.log(10) * (g_pre - g_obs) / 5) * g_obsErr)**2 + ((np.log(10) * R_sun / 5) * np.exp(np.log(10) * (g_pre - g_obs) / 5) * g_preErr)**2)")

#27
R_starErr = math.sqrt(((-np.log(10) * 695700 / 5) * np.exp(np.log(10) * (g_pre - 16.366) / 5) * 0.015)**2 + ((np.log(10) * 695700 /5 ) * np.exp(np.log(10) * (g_pre - 16.366) / 5) * g_preErr)**2)
print("#27: Error of star radius =", R_starErr)

#28
R_p = R_pFrac * R_star
print("#28: Planet radius =", R_p)

#29
R_pErr = math.sqrt((R_star * R_pFracErr)**2 + (R_pFrac * R_starErr)**2)
print("#29: Error of planet radius =", R_pErr)