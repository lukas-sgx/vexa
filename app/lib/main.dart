import 'package:flutter/material.dart';

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
		theme: ThemeData(
			colorScheme: ColorScheme.fromSeed(seedColor: const Color.fromARGB(1, 20, 30, 48)),
		),
		home: Scaffold(
			appBar: AppBar(
				title: const Text("Vexa"),
			),
			body: Center(
			child: Builder(
				builder: (context){
					return Column(
					children: [
						const Text("Hello World !"),
						const SizedBox(height: 20,),
						ElevatedButton(onPressed: (){
							print("Click!");
						},
						child: const Text('A button'),
						),
					]);
				},
				),
		),
		),
    );
  }
}