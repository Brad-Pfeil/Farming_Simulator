farm: seed.cpp vegetable.cpp grain.cpp farm.cpp farming-simulator.cpp main.cpp
	g++ -std=c++11 seed.cpp vegetable.cpp grain.cpp farm.cpp farming-simulator.cpp main.cpp -o game
test: seed.cpp vegetable.cpp grain.cpp farm.cpp farming-simulator.cpp test.cpp
	g++ -std=c++11 seed.cpp vegetable.cpp grain.cpp farm.cpp farming-simulator.cpp test.cpp -o usecase