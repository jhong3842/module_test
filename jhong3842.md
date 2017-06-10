# CTF Write Up
=====

- Bank Service
	1. diff command를 이용하여서 bank 서비스의 정규식 관련부분을 확인하였음

  REGEX_USERNAME = '^[A-Za-z0-9_]{,20}$'
  #REGEX_PASSWORD = '' # TODO: should be changed based on MySQL
  REGEX_EMAIL = '(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)'
  REGEX_PHONE = '^\d{11}$'
  REGEX_MSG = '^[A-za-z0-9\.\,_\(\)\' ]{,100}$'
  REGEX_AMOUNT = '^[0-9]*$' 
  여기서 REGEX_MSG 부분을 확인하면 sql injection에 사용될수 '(싱글쿼터)가 허용되어 있음
  
  

	2. Handling a String in C language 

	3. Chance to learned Worm and how it works

- main.c [main.c](src/main.c)

	1. IP range check, increase and port scanning of 2323 port 

	2. If victim host has a backdoor, worm login to a backdoor

	3. If login success, file check, drop, and log file of victim host


- my_worm.h [my_worm.h](src/my_worm.h)

	1. Function and global var are declated


- my_worm.c [my_worm.c](src/my_worm.c)

	1. Declation function of my_worm.h is maked in the my_worm.c

	2. gInfo var has ip, id pw 
