# C-Car-Rental-Program

# Car Rental Management System
This Car Rental Management System is a console-based application developed in C, designed to simplify the operations of a car rental business. The system provides essential features for managing cars and rental processes, offering an intuitive interface for daily tasks.

Features

Car Management:

- Add Car: Administrators can add new cars to the fleet by specifying the car's name and daily rental price. The system limits the fleet to a maximum of 10 cars.
Display Cars: This feature lists all the cars in the fleet, including details such as the car's name and current rental status (available or rented).
Rental Process:

- Rent a Car: Facilitates the entire rental process, from selecting an available car to calculating the rental cost based on the duration of the rental. Users input the rental and return dates, and the system validates these dates before proceeding. The system then updates the car's status to "rented" and stores the rental details.
Rental Summary: After the rental is completed, the system generates a summary of the rental, including the total cost, and saves this information to a file (Car_rent.txt) for record-keeping.
Data Validation:

The system includes built-in checks to validate input data, such as ensuring that dates are valid and within reasonable ranges.
Unique identifiers for cars and rentals are generated automatically, ensuring that each entry in the system is distinct.

File Handling:

The system maintains a log of all rental transactions by writing the details to a file (Car_rent.txt). This ensures that all rental activities are recorded and can be reviewed later.
Technical Details
- Programming Language: C
- Data Structures: The program utilizes structured data types (struct) to manage information about cars and rentals efficiently.
- User Interface: The system is designed with a text-based interface, providing clear prompts and easy navigation through the menu options.

This system is ideal for small car rental businesses looking to manage their operations efficiently and maintain accurate records of rental transactions.
