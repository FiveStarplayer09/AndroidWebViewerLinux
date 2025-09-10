# AndroidWebViewerLinux
AndroidWebViewerLinux

**Wellcome:** This Project created **using VS 2022** and **C++** and **QT** lib...


For Run for Use This code on Trminal:
### ભાગ ૧: તૈયારી (તમારા Windows કમ્પ્યુટર પર)

### ભાગ ૨: નિર્માણ (તમારા વેબ બ્રાઉઝરમાં)

#### પગલું ૨.૧: GitHub Codespace શરૂ કરો
1.  તમે જે રિપોઝિટરી બનાવી છે, તેના મુખ્ય પેજ પર જાઓ.
2.  લીલા રંગના **`< > Code`** બટન પર ક્લિક કરો.
3.  **`Codespaces`** ટેબ પસંદ કરો.
4.  **`Create codespace on main`** બટન દબાવો.
5.  થોડીવાર રાહ જુઓ. GitHub તમારા માટે ક્લાઉડમાં એક Linux મશીન તૈયાર કરશે અને તમારા બ્રાઉઝરમાં જ VS Code જેવું એડિટર ખુલશે.

#### પગલું ૨.૨: Codespace માં જરૂરી સાધનો ઇન્સ્ટોલ કરો
1.  Codespace માં નીચેની બાજુએ **ટર્મિનલ (Terminal)** ખુલશે. જો ન ખુલે, તો ઉપરના મેનુમાંથી `Terminal` -> `New Terminal` પર જાઓ.
2.  ટર્મિનલમાં, નીચે આપેલા કમાન્ડ્સ એક પછી એક કૉપિ-પેસ્ટ કરીને `Enter` દબાવો:

    ```bash
    # સિસ્ટમને અપડેટ કરો અને જરૂરી બિલ્ડ ટૂલ્સ ઇન્સ્ટોલ કરો
    sudo apt-get update && sudo apt-get install -y build-essential libgl1-mesa-dev

    # Qt6 અને Qt6 WebEngine ના ડેવલપમેન્ટ પેકેજો ઇન્સ્ટોલ કરો
    sudo apt-get install -y qt6-base-dev qt6-webengine-dev
    ```
    આ પ્રક્રિયામાં થોડી મિનિટો લાગી શકે છે.

#### પગલું ૨.૩: પ્રોજેક્ટને કમ્પાઇલ કરો
હવે જ્યારે બધા સાધનો ઇન્સ્ટોલ થઈ ગયા છે, ત્યારે આપણે પ્રોજેક્ટને બનાવીશું.

1.  ટર્મિનલમાં, નીચેના કમાન્ડ્સ ચલાવો:

    ```bash
    # 1. qmake ચલાવીને Makefile બનાવો (આપણે qmake6 નો ઉપયોગ કરીશું કારણ કે આપણે Qt6 ઇન્સ્ટોલ કર્યું છે)
    qmake6 FiveStarPlayerVS.pro

    # 2. make ચલાવીને કોડને કમ્પાઇલ કરો (આમાં થોડો સમય લાગી શકે છે)
    make -j$(nproc)
    ```
    *(`-j$(nproc)` એ કમ્પાઇલેશન પ્રક્રિયાને ઝડપી બનાવવા માટે કમ્પ્યુટરના બધા જ CPU કોરનો ઉપયોગ કરવાનું કહે છે.)*

2.  જો કોઈ ભૂલ વગર કમ્પાઇલેશન પૂર્ણ થાય, તો અભિનંદન! તમે સફળતાપૂર્વક તમારી એપ્લિકેશનનું Linux સંસ્કરણ બનાવી લીધું છે. ડાબી બાજુની ફાઇલ એક્સપ્લોરરમાં, તમને હવે **`FiveStarPlayerVS`** (કોઈ એક્સટેન્શન વિના) નામની એક નવી ફાઇલ દેખાશે. આ તમારી Linux એપ્લિકેશન છે.

---

### ભાગ ૩: પેકેજિંગ (`.deb` ફાઇલ બનાવવી)

હવે આપણે આ બનાવેલી એપ્લિકેશનને એક ઇન્સ્ટોલર (`.deb` ફાઇલ) માં પેક કરીશું.

#### પગલું ૩.૧: પેકેજનું માળખું બનાવો
1.  ટર્મિનલમાં, નીચેના કમાન્ડ્સ ચલાવીને જરૂરી ફોલ્ડર બનાવો:

    ```bash
    # પેકેજ માટે એક નવું ફોલ્ડર બનાવો
    mkdir -p my-app-package/DEBIAN
    mkdir -p my-app-package/usr/local/bin
    mkdir -p my-app-package/usr/share/applications
    ```

#### પગલું ૩.૨: જરૂરી ફાઈલો કૉપિ કરો
1.  આપણી બનાવેલી એપ્લિકેશનને યોગ્ય જગ્યાએ કૉપિ કરો:

    ```bash
    cp FiveStarPlayerVS my-app-package/usr/local/bin/
    ```

#### પગલું ૩.૩: કંટ્રોલ અને ડેસ્કટોપ ફાઇલ બનાવો
1.  હવે આપણે બે નાની ટેક્સ્ટ ફાઈલો બનાવવાની છે.

    **a) કંટ્રોલ ફાઇલ (`control`):** આ ફાઇલ પેકેજ વિશેની માહિતી આપે છે.
    આ કમાન્ડ ચલાવીને ફાઇલ બનાવો અને તેમાં માહિતી લખો:

    ```bash
    cat <<EOF > my-app-package/DEBIAN/control
    Package: fivestarplayer
    Version: 1.0.0
    Section: base
    Priority: optional
    Architecture: amd64
    Depends: libqt6core6, libqt6gui6, libqt6widgets6, libqt6webenginewidgets6
    Maintainer: Your Name <youremail@example.com>
    Description: Android Web Viewer
     A simple browser that mimics an Android device.
    EOF
    ```
    *(`Your Name` અને `youremail@example.com` ને તમારી વિગતોથી બદલી નાખજો.)*

    **b) ડેસ્કટોપ ફાઇલ (`.desktop`):** આ ફાઇલ એપ્લિકેશનને Linux ના એપ્લિકેશન મેનુમાં બતાવવા માટે છે.
    આ કમાન્ડ ચલાવીને ફાઇલ બનાવો:

    ```bash
    cat <<EOF > my-app-package/usr/share/applications/fivestarplayer.desktop
    [Desktop Entry]
    Version=1.0
    Name=Five Star Player
    Comment=Android Web Viewer
    Exec=/usr/local/bin/FiveStarPlayerVS
    Terminal=false
    Type=Application
    Categories=Network;WebBrowser;
    EOF
    ```

#### પગલું ૩.૪: `.deb` ફાઇલ બનાવો
1.  હવે આપણે અંતિમ કમાન્ડ ચલાવીશું જે આ બધા ફોલ્ડર્સને એક `.deb` ફાઇલમાં પેક કરી દેશે:

    ```bash
    dpkg-deb --build my-app-package
    ```
2.  બસ! આ કમાન્ડ પૂરો થયા પછી, તમને **`my-app-package.deb`** નામની એક નવી ફાઇલ દેખાશે. આ તમારી ઇન્સ્ટોલર ફાઇલ છે.

#### પગલું ૩.૫: ફાઇલ ડાઉનલોડ કરો
1.  Codespace માં ડાબી બાજુના ફાઇલ એક્સપ્લોરરમાં, **`my-app-package.deb`** ફાઇલ પર **રાઇટ-ક્લિક** કરો.
2.  **`Download`** વિકલ્પ પસંદ કરો.

હવે તમે આ `.deb` ફાઇલને કોઈપણ Ubuntu/Debian-આધારિત Linux સિસ્ટમમાં ઇન્સ્ટોલ કરી શકો છો