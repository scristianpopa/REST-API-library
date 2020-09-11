//COPYRIGHT STEFAN CRISTIAN POPA 2020//

The client runs in an infinite loop and stops only when the 'exit' command
is given. In every cycle a new connection to the server is being created and a
new command is expected.

	The accepted commands are as follows:
	- register: create a new user account
		register
		username = 'something'
		password = 'something'
	- login: login to an existing account
		login
		username = 'something'
		password = 'something'
	- enter_library: get acces to the library
		enter_library
	- add_book: add a new book to the library
		add_book
		title = 
	- get_book: get information related to a book based on its ID
	- get_books: get all the books in the library
	- delete_book: delete the book with the respective ID
	- logout: logs the client out of the current account
	- exit: stop the application

	To run the application, type 'make' and 'make run' in the terminal.