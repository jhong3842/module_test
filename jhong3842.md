# bank 서비스 취약점

  2017ctf-public/bank/server/const.py 파일을 확인해보면 정규식 부분에 변화가 있었음
  diff 명령어를  이용해서 변경된 부분을 검색하였음
 *** 2017ctf-public/bank/server/const.py	2017-05-31 01:26:25.800595181 -0700
--- ./TeamOne/server/const.py	2017-05-31 01:45:57.235424482 -0700
***************
*** 1,9 ****
  # regular expression to filter user input
! REGEX_USERNAME = '^[A-Za-z0-9_]{,20}$'
  #REGEX_PASSWORD = '' # TODO: should be changed based on MySQL
  REGEX_EMAIL = '(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)'
  REGEX_PHONE = '^\d{11}$'
- REGEX_MSG = '^[A-za-z0-9\.\,_\(\)\' ]{,100}$'
  REGEX_AMOUNT = '^[0-9]*$' 
  
