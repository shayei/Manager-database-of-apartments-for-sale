<img src="https://media.istockphoto.com/vectors/online-database-of-real-estate-line-icon-concept-online-database-of-vector-id1140788767" width="350" height="350"></a>

# Management of a database of apartments for sale

```
The program must receive "commands" from the user and execute them. The "exit" command will end the program.
It can be assumed that the input from the user is correct.
```

**Possible commands**

>	get-an-apt –MaximumPrice 1500000
- All apartments priced up to 1,500,000 NIS will be printed on the console.

>	get-an-apt –MinimumNumRooms 3
- All apartments with at least 3 rooms will be printed on the console.

>	get-an-apt –MaximumNumRooms 5
- All apartments with a maximum of 5 rooms will be printed on the console.

>	get-an-apt –Date 01052020
- All apartments vacated by tenants until May 1, 2020 will be printed on the console.

*You can combine several requirements, for example:*

>	get-an-apt –MinimumNumRooms 3 –MaximumNumRooms 5 –MaximumPrice 1750000
- All apartments with at least 3 rooms and a maximum of 5 rooms, priced up to 1,750,000 NIS will be printed on the console.

>	add-an-apt "Hasavyonim 23 Ramat Ono" 2000000 4 01 01 20
- Adding an apartment to the database at 23 Savyonim Street, Ramat Ono, which costs 2 million NIS, the number of rooms in it is 4 and the entry date is 1.1.20.

>	buy-an-apt < number >
- This order will symbolize the purchase of the apartment whose code is a < number > and will remove the apartment from the database.
  
>	get-an-apt –Enter < x > 
- The codes of the apartments that entered the database in the last < x > days will be printed.
  
>	delete-an-apt –Enter < x >
- The apartments that entered the database in the last < x > days will be removed.

> get-an-apt –MaximumNumRooms 5 -sr
- To each of the above commands you can add the option -s and get the information sorted from the lowest price to the highest price, or the option -sr and get the information sorted from the highest price to the lowest.

---
### Software usage history
<img src="https://www.roehampton.ac.uk/globalassets/images/course-pages/postgraduate/history.jpg" width="700" height="150"></a>

```
The commands are stored in one of two repositories:
A - Short history database by array
B - Long history database by linked list
```

**Possible commands**
> !!
- Command !! Will cause further execution of the last command entered in database A.

> !< num > 
- This command will execute the command with the specified number num. 

> short_history
-  This command will print the 7 most recent commands (Database A).

> history 
- This command will print both databases A and B.

> !< num >^str1^str2 
- This command will execute the command number < num > which contains a str1 string in which it will be replaced with a str2 string.

*The commands will be saved in a text file between runs of a program and therefore commands given in a previous run of the program can also be restored.*

---

### Saving apartments in a binary file
<img src="https://cdn-learn.adafruit.com/guides/cropped_images/000/001/957/medium640/90486-OIL5JT-758.jpg?1521650913" width="700" height="150">

Apartment code - will be saved as a 'short int' binary number.
Apartment address - the length of the string will be kept in the 'short int' and then the string (without '0 \').
The price of the apartment - will be saved as an 'int' binary type

The other fields are limited in size:

Number of rooms - it is known that there will be a maximum of 15 rooms, so 4 bits are enough
Date of entry to the apartment - day - 5 bits are enough
Month - 4 bits are enough
One year - 7 bits are enough

For information regarding the number of rooms and the date of entry, 20 bits, ie 3 bytes, are sufficient.
We will use 3 bytes when the bits are stored in them as follows:

The 4 most significant bits will mark the number of rooms
The 5 bits that follow will mark the day of entry
The 4 bits that follow will mark the month of entry
The 7 bits that follow will mark the year of entry

## ENJOY
