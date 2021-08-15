# ascii-pandemic-game
A simple ASCII strategic game written in C++ where you build a city and defend it from a deadly pandemic.
I wrote this game as part of my semestral project.

# Gameplay
Simple ASCII gui.

![game gui](http://bobby-tran.wezi.cz/images/projects/covid.JPG)

You play by using your mouse, clicking on the map and highlighted buttons.

Game settings and configuration can be altered in examples folder.

The epidemic starts in X seconds, your mission is to build a city and prepare for it.

The game ends when either all citizens in the city die or you successfully develop a vaccine.

## Buildings
- Residential - summons citizens
- Hospital - employs doctors, isolates and treats infected - the speed of treatment is relative to the number of emplyed doctors in each hospital
- Business - employs entrepreneurs, generates money
- University - produces doctors, scientists and entrepreneurs - the distribution is randomized but also depends on the investment into healthcare and science
- Laboratory - employs scientists, developes vaccine - the speed of vaccine development is relative to the number of employed scientists, there is also a high chance that the development will fail

## Other actions
- Invest into stocks - increases food supply in case of lockdown
- Invest into healthcare - increases the chances for students to graduate as doctors
- Purchase facemasks - in case of introducing mandatory facemasks
- Invest into science - increases the chances for students to graduate as scientists, also decreases the chance of failing the vaccine research
- Introduce mandatory facemasks - reduces the number R by 0.2
- Close schools - reduces the number R by 0.5
- Close businesses - reduces the number R by 0.8
- Lockdown - reduces the number R to 0, depending on the food supply, people might start dying from starvation and start protesting
