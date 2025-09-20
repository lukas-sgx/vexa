import 'package:http/http.dart' as http;
import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:material_symbols_icons/symbols.dart';
import 'package:flutter_nfc_kit/flutter_nfc_kit.dart';
import 'package:local_auth/local_auth.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Vexa',
      home: DashPage(),
    );
  }
}

class DashPage extends StatefulWidget {
  const DashPage({super.key});

  @override
  State<DashPage> createState() => _Dashboard();
}


class _Dashboard extends State<DashPage> {
  int _selectedIndex = 0;
  int _selectedCard = 0;

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
  }

  String shortIban(String iban) {
    return "${iban.substring(0, 4)}***${iban.substring(iban.length - 4)}";
  }


  // void _onCardChanged(int index) {
  //   setState(() {
  //     _selectedCard = index;
  //   });
  // }

  Future<double> _getSold() async {
    var response = await http.post(
      Uri.parse("http://192.168.86.197:5500/api/connected.php"),
      body: {
        "number": "1",
        "cmd": "getSold",
      },
    );
    final data = jsonDecode(response.body);
    return double.parse(data["solde"].toString());
  }


  var _error;

  Future<void> addPay() async {
    var response = await http.post(
      Uri.parse("http://192.168.86.197:5500/api/connected.php"),
      body: {
        "number": "1",
        "cmd": "payment",
        "iban": "FR7619106006001000000000024",
        "toiban": "FR7619106006002000000000029",
        "price": _tagInfo ==  "943BCE07663C16E0" ? "16.0" : _tagInfo == "04336DBABA7780" ? "9.99" : _tagInfo == "F7E19805" ? "990" : "null",
        "name": _tagInfo ==  "943BCE07663C16E0" ? "Isola 2000" : _tagInfo == "04336DBABA7780" ? "Oyster London" : _tagInfo == "F7E19805" ? "Epitech" : "null",
      },
    );
    
    response.statusCode == 200 ? _error = 0 : _error = 1;
  }

  Future<List<dynamic>> _getLastTransactions(limit) async {
    var response = await http.post(
      Uri.parse("http://192.168.86.197:5500/api/connected.php"),
      body: {
        "iban": "FR7619106006001000000000024",
        "cmd": "getLastTransactions",
        "limit": "$limit",
      },
    );

    if (response.statusCode == 200) {
      final List<dynamic> data = jsonDecode(response.body);
      return data;
    } else {
      throw Exception("Erreur serveur: ${response.statusCode}");
    }
  }

  void _buildSheet(BuildContext context) {
    final futureTransactions = _getLastTransactions(20);

    showModalBottomSheet(
      context: context,
      isScrollControlled: true,
      builder: (BuildContext context) {
        return Padding(
          padding: const EdgeInsets.all(16),
          child: FutureBuilder<List<dynamic>>(
            future: futureTransactions,
            builder: (context, snapshot) {
              if (snapshot.connectionState == ConnectionState.waiting) {
                return Center(child: CircularProgressIndicator());
              } else if (snapshot.hasError) {
                return Text("Erreur : ${snapshot.error}");
              } else if (!snapshot.hasData || snapshot.data!.isEmpty) {
                return Text("Aucune transaction trouvée");
              } else {
                final transactions = snapshot.data!;
                final shouldScroll = transactions.length > 6; 
                final listWidget = ListView.builder(
                  itemCount: transactions.length,
                  physics: shouldScroll ? BouncingScrollPhysics() : NeverScrollableScrollPhysics(),
                  shrinkWrap: !shouldScroll, 
                  itemBuilder: (context, index) {
                    final t = transactions[index];
                    final price = (t['price'] as num).toDouble();
                    final displayIban = price >= 0
                        ? shortIban(t['toacc'])
                        : shortIban(t['toacc']);
                    return _buildTile(
                      t["type"] != "card" ? displayIban : t["name"],
                      t['date'],
                      t['type'],
                      price,
                    );
                  },
                );

                return Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Text(
                      "Transaction History",
                      style: TextStyle(
                        fontFamily: "Montserrat",
                        fontSize: 16,
                        fontWeight: FontWeight.w600,
                      ),
                    ),
                    SizedBox(height: 16),
                    shouldScroll
                        ? SizedBox(
                            height: 300, // hauteur max avant scroll
                            child: listWidget,
                          )
                        : listWidget,
                  ],
                );
              }
            },
          ),
        );
      },
    );
  }


  Widget _buildTile(title, subtitle, type, amount) {
    return Padding(
      padding: const EdgeInsets.only(bottom: 8.0, top: 8),
      child: 
      Row(
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: [
          Row(
            children: [
              Container(
                padding: EdgeInsets.all(10),
                decoration: BoxDecoration(
                  borderRadius: BorderRadius.circular(50),
                  color: const Color.fromARGB(221, 20, 18, 133)
                ),
                child: 
                  Icon(type == "card" ? Symbols.credit_card : type == "levy" ? Symbols.upload : Symbols.sync_alt, color: Colors.white, size: 26,),
              ),
              SizedBox(width: 10),
              Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(title, style: TextStyle(color: Color.fromRGBO(16, 20, 18, 1), fontFamily: "Montserrat", fontWeight: FontWeight.normal, fontSize: 15),),
                  Text(subtitle,  style: TextStyle(color: Color.fromRGBO(116, 119, 120, 1), fontFamily: "Montserrat", fontWeight: FontWeight.normal, fontSize: 13)),
                ],
              ),
            ],
          ),
          Column(
            crossAxisAlignment: CrossAxisAlignment.end,
            children: [
              Text('$amount €', style: TextStyle(color: Color.fromRGBO(16, 20, 18, 1), fontFamily: "Montserrat", fontWeight: FontWeight.normal, fontSize: 15),),
              Text(amount >= 0 ? "credit" : "debit",  style: TextStyle(color: amount >= 0 ? const Color.fromARGB(255, 16, 185, 129) : const Color.fromARGB(255, 238, 68, 68), fontFamily: "Montserrat", fontWeight: FontWeight.normal, fontSize: 13)),
            ],
          ),
        ],
      ),
    );
  }

final LocalAuthentication auth = LocalAuthentication();

bool _auth = false;
Future<void> authenticateUser() async {
  if(!_auth){
    try {
      bool isAvailable = await auth.canCheckBiometrics;
      bool didAuthenticate = await auth.authenticate(
        localizedReason: 'Veuillez vous authentifier pour payer',
        options: const AuthenticationOptions(
          biometricOnly: false, // autorise aussi le code
          stickyAuth: true,
        ),
      );

      if (didAuthenticate) {
        print("✅ Authentification réussie !");
        _auth = true;
        startNfcScan();
      } else {
        print("❌ Échec de l'authentification.");
      }
    } catch (e) {
      print("Erreur d'authentification : $e");
    }
  }
}


String _tagInfo = "Aucun tag";
bool _isScanning = false;

Future<void> startNfcScan() async {
  
  if (_isScanning || !_auth) return; // évite de lancer plusieurs scans
    _isScanning = true;

    NFCTag tag = await FlutterNfcKit.poll(timeout: Duration(seconds: 30));
    String uid = tag.id ?? "UID non trouvé";
    print("Numéro de série : $uid");

    setState(() {
      _tagInfo = uid;
    });

    addPay();

    await FlutterNfcKit.finish();
    setState(() {
      _auth = false;
    });
    _onItemTapped(0);
    _isScanning = false;
}


  Widget _buildContent(){
    DateTime now = DateTime.now();
    int hour = now.hour;
    var futureTransactions = _getLastTransactions(3);

    if(_selectedIndex == 0){
      return Column(
        children: [
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              (() {
                if (hour >= 6 && hour < 12) {
                  return Text("Good Morning, Lukas!",
                    style: TextStyle(
                      fontFamily: "Montserrat",
                      fontSize: 15,
                      color: Color.fromRGBO(124, 132, 163, 1),
                    ),
                  );
                } else if (hour >= 12 && hour < 18) {
                  return Text("Good Afternoon, Lukas!",
                    style: TextStyle(
                      fontFamily: "Montserrat",
                      fontSize: 15,
                      color: Color.fromRGBO(124, 132, 163, 1),
                    ),
                  );
                } else {
                  return Text("Good Evening, Lukas!",
                    style: TextStyle(
                      fontFamily: "Montserrat",
                      fontSize: 15,
                      color: Color.fromRGBO(124, 132, 163, 1),
                    ),
                  );
                }
              })(),
            ],
          ),
          
          Padding(
            padding: const EdgeInsets.only(top: 15),
            child: 
              Row(
                mainAxisAlignment: MainAxisAlignment.start,
                children: [
                    Text("Total Balance", style: TextStyle(fontFamily: "Montserrat", fontSize: 17, color: Color.fromRGBO(98, 100, 107, 1))),
                ],
              ),
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.start,
            children: [
              FutureBuilder<double>(
                future: _getSold(),
                builder: (context, snapshot) {
                  if (snapshot.connectionState == ConnectionState.waiting) {
                    return CircularProgressIndicator();
                  } else if (snapshot.hasError) {
                    return Text("Erreur : ${snapshot.error}");
                  } else if (snapshot.hasData) {
                    return Text("€ ${snapshot.data!.toStringAsFixed(2)}", style: TextStyle(fontFamily: "Montserrat", fontSize: 40, color: Color.fromRGBO(29, 32, 88, 1), fontWeight: FontWeight.bold));
                  } else {
                    return Text("Aucune donnée reçue");
                  }
                },
              )
              
            ],
          ),
              
          Padding(
            padding: const EdgeInsets.only(top: 15),
            child: 
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  OutlinedButton.icon(
                    onPressed: () {
                    },
                    icon: Icon(Icons.north_east, color: Color.fromRGBO(29, 32, 88, 1)),
                    label: Text('Send Money', style: TextStyle(fontFamily: 'Montserrat'),),
                    style: OutlinedButton.styleFrom(
                      side: BorderSide(color: Colors.blue),
                      foregroundColor: Color.fromRGBO(29, 32, 88, 1),
                      padding: EdgeInsets.symmetric(horizontal: 30, vertical: 17),
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(50),
                      ),
                    ),
                  ),
                  OutlinedButton.icon(
                    onPressed: () {
                    },
                    icon: Icon(Icons.south_west, color: Color.fromRGBO(29, 32, 88, 1)),
                    label: Text('Receive Money', style: TextStyle(fontFamily: 'Montserrat'),),
                    style: OutlinedButton.styleFrom(
                      side: BorderSide(color: Colors.purple),
                      foregroundColor: Color.fromRGBO(29, 32, 88, 1),
                      padding: EdgeInsets.symmetric(horizontal: 30, vertical: 17),
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(50),
                      ),
                    ),
                  ),
                ],
              ),
          ),
          SizedBox(height: 16),
          _buildCard(),
          SizedBox(height: 16),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Text("Transaction History", style: TextStyle(fontFamily: "Montserrat", fontSize: 16, color: Color.fromARGB(255, 6, 7, 7), fontWeight: FontWeight.w500),),
              TextButton(
                onPressed: () => _buildSheet(context),
                style: TextButton.styleFrom(
                  padding: EdgeInsets.zero,
                  minimumSize: Size(0, 0), 
                  tapTargetSize: MaterialTapTargetSize.shrinkWrap,
                ).copyWith(
                  overlayColor: MaterialStateProperty.all(Colors.transparent),
                ),
                child: 
                  Text("See all", style: TextStyle(fontFamily: "Montserrat", fontSize: 16, color: Color.fromARGB(255, 75, 92, 209), fontWeight: FontWeight.w500),),
              ),
            ],
          ),
          Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              FutureBuilder<List<dynamic>>(
                future: futureTransactions,
                builder: (context, snapshot) {
                  if (snapshot.connectionState == ConnectionState.waiting) {
                    return CircularProgressIndicator();
                  } else if (snapshot.hasError) {
                    return Text("Erreur : ${snapshot.error}");
                  } else if (!snapshot.hasData || snapshot.data!.isEmpty) {
                    return Text("Aucune transaction trouvée");
                  } else {
                    final transactions = snapshot.data!;

                    return Column(
                      children: transactions.map((t) {
                        final price = (t['price'] as num).toDouble();
                        final displayIban = price >= 0
                          ? shortIban(t['fromacc'])
                          : shortIban(t['toacc']); 
                        return _buildTile(
                          t["type"] != "card" ? displayIban : t["name"], // titre
                          t['date'],   // sous-titre
                          t['type'],   // type
                          price,       // montant
                        );
                      }).toList(),
                    );
                  }
                },
              ),
            ],
          ),



          
          // Container(
          //   height: 1,
          //   decoration: BoxDecoration(
          //     gradient: LinearGradient(
          //       colors: [
          //         Colors.transparent,
          //         const Color.fromARGB(255, 190, 190, 190),
          //         Colors.transparent,
          //       ],
          //     ),
          //   ),
          // ),
        ],
      );
    }else if(_selectedIndex == 1){
      return Column(
        children: [
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Text("My Wallet", style: TextStyle(fontFamily: "Montserrat", fontSize: 20, color: Color.fromRGBO(29, 32, 88, 1),),),
              IconButton(
                onPressed: () => print("dots for dashboard"),
                icon: Icon(Symbols.more_horiz, fontWeight: FontWeight.bold,),
                iconSize: 28,
              ),
            ],
          ),
          _buildCard(),
          SizedBox(height: 10,),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Padding(
                padding: const EdgeInsets.only(left: 2.5, right: 2.5),
                child: 
                  Container(
                    height: 10,
                    width: 10,
                    decoration: BoxDecoration(
                      color: _selectedCard == 0 ? Colors.black : Colors.grey,
                      borderRadius: BorderRadius.circular(50),
                    ),
                  ),
              ),
              Padding(
                padding: const EdgeInsets.only(left: 2.5, right: 2.5),
                child: 
                  Container(
                    height: 10,
                    width: 10,
                    decoration: BoxDecoration(
                      color: _selectedCard == 1 ? Colors.black : Colors.grey,
                      borderRadius: BorderRadius.circular(50),
                    ),
                  ),
              ),
              Padding(
                padding: const EdgeInsets.only(left: 2.5, right: 2.5),
                child: 
                  Container(
                    height: 10,
                    width: 10,
                    decoration: BoxDecoration(
                      color: _selectedCard == 2 ? Colors.black : Colors.grey,
                      borderRadius: BorderRadius.circular(50),
                    ),
                  ),
              ),
            ],
          )
        ],
      );
    }else if(_selectedIndex == 2){
      authenticateUser();
      return SizedBox.expand( // prend tout l'espace de l'écran
    child: Align(
      alignment: Alignment.center, // centre verticalement et horizontalement
      child: Column(
        mainAxisSize: MainAxisSize.min, // ne prend que la taille du contenu
        crossAxisAlignment: CrossAxisAlignment.center,
        children: [
          Container(
            padding: EdgeInsets.all(17),
            decoration: BoxDecoration(
              borderRadius: BorderRadius.circular(50),
              color: Color.fromRGBO(29, 32, 88, 1),
            ),
            child: Icon(
              Symbols.lift_to_talk,
              color: Colors.white,
              size: 55,
            ),
          ),
          SizedBox(height: 7),
          Text(
            "Hold card near phone",
            style: TextStyle(
              fontSize: 20,
              fontFamily: "Montserrat",
              fontWeight: FontWeight.bold,
            ),
          ),
        ],
      ),
    ),
  );
    }else{
      return Text("Error: not found Index");
    }
  }

  Widget _buildCard() {
  return Container(
            height: 200,
            decoration: BoxDecoration(
              borderRadius: BorderRadius.circular(20),
              gradient: LinearGradient(
                colors: [Color.fromARGB(255, 34, 38, 91), Color.fromARGB(255, 39, 47, 144)],
                begin: Alignment.topLeft,
                end: Alignment.bottomRight,
              ),
              boxShadow: [
                BoxShadow(
                  color: Colors.black26,
                  blurRadius: 8,
                  offset: Offset(0, 4),
                ),
              ],
            ),
            padding: EdgeInsets.all(20),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Image.asset("assets/img/visa.png", height: 25,),
                    Icon(Icons.contactless_outlined, color: Colors.white),
                  ],
                ),

                SizedBox(height: 15),
                Padding(
                  padding: const EdgeInsets.only(left: 15),
                  child: 
                    Image.asset("assets/img/chip.png", height: 45,),
                ),
                SizedBox(height: 17),

                Text(
                  '**** **** 8092 7654',
                  style: TextStyle(
                    color: Colors.white,
                    fontSize: 20,
                    letterSpacing: 2,
                  ),
                ),
                SizedBox(height: 8),
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Text('Mr. Lukas Soigneux', style: TextStyle(color: Colors.white)),
          
                    SizedBox(height: 8),
                    Text('12/25', style: TextStyle(color: Colors.white)),
                  ]
                ),
              ],
            ),
  );
}



  @override
  Widget build(BuildContext context) {
    return Scaffold(
      extendBody: true,

      backgroundColor: Color.fromARGB(255, 248, 248, 248),

      body: 
          Padding(
            padding: const EdgeInsets.only(left: 20, right: 20,),
            child: 
              Column(
                children: [
                  Padding(
                    padding: const EdgeInsets.only(top: 50, bottom: 20),
                    child: 
                        Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          crossAxisAlignment: CrossAxisAlignment.center,
                          children: [
                            Image.asset("assets/img/logo.png", height: 40,),
                            IconButton(
                              onPressed: () => print("dots for dashboard"),
                              icon: Icon(Symbols.notifications,),
                              iconSize: 28,
                            ),
                          ],
                        ),
                  ),
                  Expanded(
                    child: _buildContent(),
                  ),
                ],
              ),
            ),

      bottomNavigationBar: Container(
        margin: const EdgeInsets.all(40),
        height: 70,
          
        decoration: BoxDecoration(
          color: Colors.white,
          borderRadius: BorderRadius.circular(50),
          boxShadow: [
            BoxShadow(
              color: Colors.black12,
              blurRadius: 50,
              offset: const Offset(5, 5),
            ),
          ],
        ),

        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            IconButton(
              onPressed: () => _onItemTapped(0),
              icon: Icon(
                Symbols.home,
                size: 28,
                color: Color.fromRGBO(12, 12, 57, 1),
                fill: _selectedIndex == 0 ? 1 : 0,
              ),
            ),
            IconButton(
              onPressed: () => _onItemTapped(1), 
              icon: Icon(
                Symbols.credit_card,
                size: 28,
                color: Color.fromRGBO(12, 12, 57, 1),
                fill: _selectedIndex == 1 ? 1 : 0,
              ),
            ),
            IconButton(
              onPressed: () => _onItemTapped(2), 
              icon: Icon(
                Symbols.contactless,
                size: 28,
                color: Color.fromRGBO(12, 12, 57, 1),
                fill: _selectedIndex == 2 ? 1 : 0,
              ),
            ),
            IconButton(
              onPressed: () => _onItemTapped(3), 
              icon: Icon(
                Symbols.sync_alt,
                size: 28,
                color: Color.fromRGBO(12, 12, 57, 1),
                fill: _selectedIndex == 3 ? 1 : 0,
              ),
            ),
            IconButton(
              onPressed: () => _onItemTapped(4), 
              icon: Icon(
                Symbols.settings,
                size: 28,
                color: Color.fromRGBO(12, 12, 57, 1),
                fill: _selectedIndex == 4 ? 1 : 0,
              ),
            ),  
          ],
        ),
      ),
    );
  }
}