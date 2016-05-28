#!/bin/bash

echo "Skrypt wysyla, a następnie odbiera komunikat pod pewnymi warunkami, oraz sprawdza jego występowanie w słowniku języka polskiego"

./sender
./recipient

zm=`cat word.data | head -1`
zm2=`echo "$zm" | aspell -a --lang=pl`
gwiazdka=$(echo "$zm2" | sed -n 2p)
echo "$gwiazdka" #test
if [[ `echo $gwiazdka` == "*" ]] #Zauważyłem, że jeśli słówko jest w jężyku polskim to aspell wypisuje gwiazdkę w drugiej linii.
				 #Chciałem to wykorzystać w ifie, jednak nie mam pojęcia dlaczego to nie działa
then
	echo "To slowo istnieje w slowniku"
else
	echo "To slowo nie istnieje w jezyku polskim"
fi
