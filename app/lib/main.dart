import 'package:flutter/material.dart';
import 'package:material_symbols_icons/symbols.dart';


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

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
  }


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      extendBody: true,

      backgroundColor: Color.fromARGB(255, 248, 248, 248),

      body: Column(
        children: [
          Padding(
            padding: const EdgeInsets.only(left: 20, top: 50, right: 20, bottom: 30),
            child: 
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: [
                    Image.asset("assets/img/logo.png", height: 40,),

                    IconButton(
                      onPressed: () => print("dots for dashboard"),
                      icon: Icon(Symbols.notifications, ),
                      iconSize: 28,
                      
                    ),
                  ],
                ),
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text("Good Morning, Lukas!", style: TextStyle(fontFamily: "Montserrat", fontSize: 15, color: Color.fromRGBO(124, 132, 163, 1)),),
            ],
          ),
        ],
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
                Symbols.sticky_note_2,
                size: 28,
                color: Color.fromRGBO(12, 12, 57, 1),
                fill: _selectedIndex == 2 ? 1 : 0,
              ),
            ),
            IconButton(
              onPressed: () => _onItemTapped(3), 
              icon: Icon(
                Symbols.settings,
                size: 28,
                color: Color.fromRGBO(12, 12, 57, 1),
                fill: _selectedIndex == 3 ? 1 : 0,
              ),
            ),  
          ],
        ),
      ),
    );
  }
}