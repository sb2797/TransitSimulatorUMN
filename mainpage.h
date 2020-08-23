// Copyright 2020 @author Srivatsan Balaji

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage Bus Simulation
*
* \section Introduction
*
*@details Transit Simulator is a program designed to simulate
* the University Of Minnesota-Twin Cities "GopherTrip" application.
* There are many applications such as GopherTrip application, but the
* Transit Simulator will be running on running on a web server with some different
* functionalities. Users will be able to adjust the number of time steps to
* run and time steps between busses for route. The minimum number of time steps
* to run is 1 and maximum is 90. The minimum time steps between busses for route
* is 1 and maximum is 30.
*
***************
* \section Classes
 *@details Class Bus, Route, Stop, and Passenger has a special relationship.
 * Every time Bus class calls its @param Update(),
 * it will trigger @param Update() in Passneger to update the passengers
 * time on bus. It will also call functions in
 * Route such as @param GetDestinationStop(), @param GetNextStop(),
 * and etc depends on the bus and passnger status (the bus
 * should not stop if there is no passenger to load or unload and
 * the speed is fast that it should skip a stop
 * or it should if there are passenger to load and unload
 * regradless of the speed and if the distance remaning
 * to stop is zero or a negative number.)
 *
 * \subsection Simulator
 *@details The purpose of Simulator class is to start the Transit Simulator
 * by creating buses,
 * stops, routes, distance between routes and passengers.
 * @param Start() and @param Update() functions
 * are a pure virtual boolean function that implemented in LocalSimulator.
 *
 * \subsection LocalSimulator
 * @details LocalSimulator class is the child of Simulator.
 * @param Start() will create routes with stops and generates passengers.
 * @param Update() will update passengers, stops, and buses status for each
 * simulation time.
 *
 * \subsection PassengerFactory
 * @details PassengerFactory class is the main class that generates passengers.
 * It generates a
 * passenger with a randomized name and random destination with bounds when
 * @param Generate(curr_stop, last_stop) is called each time. In order to
 * set the bound
 * , pass in currect stop id and last stop id into the function. The function
 * will return Passenger object with name and destination
 *
 * \subsection PassengerGenerator
 * @details PassengerGenerator is a constructor that constructs a
 * passenger generator with a list of
 * propabilities and a list of stops called
 * @param in generation_probabilities_ and stops_
 * respectively.
 *
 *@details GeneratePassengers() is a pure virtual function
 * in Passenger Generator. It is
 * is implemented in RamdomPassengerGenerator class. It will return number of
 * passenger has been generated.
 *
 * \subsection RandomPassengerGenerator
 * @details RandomPassengerGenerator class is
 * inheritance of PassengerGenerator class.
 *
 *@details RandomPassengerGenerator constructor constructs a random passenger
 * generator
 * with a list of probabilities and a list of stops called probs
 * and stops respectively.
 *
 * @param GeneratePassengers() will randomly generates passengers for each stops
 * according to propabilities and return number of passenger generated.
 * After calling the Generate function from
 * PassengerFactory to generate a passenger, it will add the passenger
 * to current stop by
 * calling Stop @param AddPassengers(passenger) which takes in a passenger and
 * add to the Stop passenger list.

 * \subsection Passenger
 * @details Passenger class is a simple class that with several functions
 * that used update
 * and get passengers status and information. It is also used to test
 * to see if the program works well.
 * Each time the @param out Update() function is called, passengers time status
 * on bus or at stop will be updated.
 * This function will be called in Stop @param Update() and @param Bus Update().
 *
 * \subsection Stop
 *@details Stop class is a class that form a route. It will also
 * update the passengers
 * status at stop when its Update function is called. Each stops has an
 * unique id and longitude and latitude based on real world location.
 *  To load passengers on bus,
 * a bus is passed into the LoadPassengers(bus) when it is called.
 * Stop LoadPassengers will call Bus LoadPassenger to add passengers at the stop
 * onto the bus when bus arrived and there is spaces. It will number
 * of passengers add to Bus and delete passengers loaded onto the bus
 * from Stop passenger list.
 * Report function will print the stops status and the output can be
 * redirect to a file.
 *
 * \subsection Route
 * @details Route class is a class that keeps a list of stops.
 * Each route has a name, a list of stops, a list of distances between each
 * stops, number of stops.
 * It can also generate passengers by using PassengerGenerator* generator_.
 * Similar to Stop Report, Report function will print the stops status
 * and the output can be redirect to a file. Route has a clone methods will
 * deep copy constructor. Route Update() will update each stops in the route
 * and stops will update passengers status in each stops.
 *
 *\subsection Bus
 *@details Bus class, like the buses in real world, has passengers, outgoing
 * and incoming routes, speed, and name.
 * It will move based on its speed and stop at every stops.
 * When Update function is called the bus will move closer to the next stop.
 * It will load and unload passengers at stops by calling stops'
 * Update function. Once the bus completes its outgoing and incoming
 * routes it will be deleted.
 *
 *****************
 * \subsection  Running the Simulator
 * \subsection Method 1 Run on VOLE or CSE labs machines
 * 1. Navigate to base project directory
 * 2. Make and start server:
 *
 *
 * $ cd src
 * $ make <sim targer>
 * $ cd ..
 * $ ./build/bin/<sim executable> <port number>
 *
*
 * Notes:
 * i. The port number can be anything but it is recommended to be in
 * the range of 8000 to not multiples of 10.
 *
 * ii. You must run ./build/bin/<sim executable> <port_number>
 * at base project directory or it won't work.
 *
 * 3. Open a broswer you like and navigate to the following address:
 *
 * http://127.0.0.1:<port_number>/web_graphics/project.html
 *
*
 * 4. Once you get to the simulation page, adjust the time steps and
 * time steps between busses to your desire number and then click
 * the Start button. If you wish to run a time steps greater
 * than 50, you can refersh the browser, make adjustment, click
 * the start button and repeat.
 *
 * \subsection Method 2 Using SSH
 * 1. SSH to cse labs machines using the following command:
 *
 * ssh -L <port number>:127.0.0.1:<port_number> <x500>@<cse_labs_computer>.cselabs.umn.edu
 *
*
 * Notes:
 * i. The port number can be anything but it is recommended to be in
 * the range of 8000 to not multiples of 10.
 *
 * ii. <x500> is your Internet ID
 *
 * iii. Refer to the following link to get the CSE Labs UNIX
 * Machine Listings
 *
 * https://cseit.umn.edu/computer-classrooms/cse-labs-unix-machine-listings
 *
*
 * After successfully connected to the CSE labs machine:
 * 1. Navigate to base project directory
 * 2. make and start server:
 *
 * $ cd src
 * $ make <sim target>
 * $ cd ..
 * $ ./build/bin/<sim executable> <port_number>
 *
*
 * Notes:
 * i. The port number can be anything but it is recommended to be in
 * the range of 8000 to not multiples of 10.
 *
 * ii. You must run ./build/bin/<sim executable> <port_number>
 * at base project directory or it won't work.
 *
 * 3. Open a browser you like on your local machine and navigate to the
 * following address:
 *
 * http://127.0.0.1:<port_number>/web_graphics/project.html
 *
* 4. Once you get to the simulation page, adjust the time steps and
 * time steps between busses to your desire number and then click
 * the Start button. If you wish to run a time steps greater
 * than 50, you can refersh the browser, make adjustment, click
 * the start button and repeat.
 *
 *************************
 * Pros and Cons of Factory Concrete vs Abstract Factory:
 *
 * Advantages of Factory Concrete: It eliminates the need to bind application-specific
 * classes into my code. It can connect parallel class hierarchies in such a way
 * that it localizes the knowledge of which classes belong together.
 *
 * Disadvantages of Factory: The potential disadvantage of Factory is that
 * clients mighthave to sub-class the creator class just to create a particular
 * product.
 *********
 * Advantages of Abstract Factory: We can use the Abstract Factory to control
 * the classes of objects the clients create. The client code will not break
 * because the abstract interfaces don't change frequently. Abstract Factory can
 * a family of products.
 *
 * Disadvantages of Abstract Factory: Adding a new product will require
 * extending the abstract interface which implies that all of its derived
 * concrete class must change.
 *********************ITERATION 2******************************
 * Designing and Implementing the Observer Pattern
 * @brief IObservable.h :
 * @details
 * void RegisterObserver(IObserver* Observer); - The responsibility of observers
 is to register (and unregister) themselves
 on a subject (to get notified of state changes) and to update their state
 (synchronize their state with subject's state) when they are notified.
 * void ClearObservers();
 * void NotifyObservers(BusData* info); - The notifyObservers() method notify
 * all of its observers if the object has changed. This method later calls the
 * ClearObservers method to indicate that this object has no longer changed.
 * This method is equivalent to notifyObservers(null).
 *
 * @brief IObserver.h
 * @details
 * NotifyObservers() -Checks the internal flag to see if the observable
 * has changed state
 * and notifies all observers.
 *
 * @brief bus_factory.h -
 * @details
 * It is in charge of the bus's routes, speed and directions.
 *
 * @brief bus.h
 * @details
 * bool IsTripComplete();
 *
 * @brief Report
 * outputs the bus's information then calles report on all its passengers
 *
 * bool LoadPassenger(Passenger *);  // returning revenue delta
 * @param[in] passenger* for passenger to be added to bus
 * @return bool if the passenger being added successfully got on the bus
 *
 * bool Move();
 *  @return bool if the move function was successfully
 * updates the bus's distance_remaining_ based on its speed
 *
 * void Update();
 * while there the route isn't at the end it calls move()
 * once the bus makes it to the next stop it first UnloadPassengers
 * then it LoadPassenger from the stop and finally it updates route with
 * nextStop()
 * once the outbound route is at the end it switches to the incoming_route_
 *
 * void Report(std::ostream&);
 *
 * void UpdateBusData();
 * Called every time update is called to update the bus_info_ bus_data
 * data_struct to be updated with the latest information
 *
 * BusData GetBusData() const;
 * int UnloadPassengers();  // returning revenue delta
 * removes passengers on bus whose destination_stop_id matches there
 * destination id
 *
 * @brief Visualization_Simulator.h
 * @brief my_web_server_command.h
 * * @remark The Observer Pattern defines a one to many dependency between objects
 * so that one object changes state, all of its dependents are notified and
 * updated automatically. Explanation: One to many dependency is between
 * Subject(One) and Observer(Many). There is dependency as Observers themselves
 * don't have access to data.
 * *
 *********************************************************************
 *********************************************************************
 ITERATION 3
 2 Alternative Implementations of the Decorator Pattern:
 I.) Module + extend + super Decorator
 Benefits: It delegates through all decorators.
 It has all of the original interface because it is the original object.
 Negatives: It cannot be used the same decorator more than once.
 It is difficult to tell which decorator added the functionality.

 II.) SimpleDecorator + super + getobj decorators
 Benefits: Can be wrapped infinitely using Ruby instantiation.
 delegates through all decorators.
 can use same decorators more than once on component.
 Negatives: It redefines its class.

 Decorator Pattern:
 Pros: Decorators provide a flexible alternative to subclassing for extending
 functionality. It allows behavior modification at runtime rather than going
 back into existing code and making changes. Decorators are a nice solution to
 permutation issues because you can wrap a component with any number of
 decorators. The decorator pattern supports the principle that classes should
 be open for extension but closed for modification.

 Cons: Decorators can result in many small objects in our design, and overuse
 can be complex. Decorators can also cause issues if the client relies heaviliy
 on the component concrete type. Decorators can complicate the process of
 instantiating the component because you not only have to instantiate the
 component but wrap it in a number of decorators. It can be complicated to have
 decorators keep track of other decorators because to look back into multiple
 layers of the decorator chain starts to push the decorator pattern beyond its
 true intent.
 */

#endif  // SRC_MAINPAGE_H_
