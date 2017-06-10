# bank 서비스 취약점

  2017ctf-public/bank/server/const.py 파일을 확인해보면 정규식 부분에 변화가 있었음
  diff 명령어를  이용해서 변경된 부분을 검색하였음

  REGEX_USERNAME = '^[A-Za-z0-9_]{,20}$'
  #REGEX_PASSWORD = '' # TODO: should be changed based on MySQL
  REGEX_EMAIL = '(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)'
  REGEX_PHONE = '^\d{11}$'
  REGEX_MSG = '^[A-za-z0-9\.\,_\(\)\' ]{,100}$'
  REGEX_AMOUNT = '^[0-9]*$' 
  
