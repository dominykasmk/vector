# Custom vektor klasė

Implementavau savo vektor klasę, kurią ištestavau ir panaudojau su studentų klase

## Kaip parunnint

 - `git clone https://github.com/dominykasmk/vector.git`
 - `cd vector`
 - `cmake -S src/ -B out/`
 - `cd out/ && make`
 - `./main`

## Testai
 
 
## Pratestavau 5 skirtingaų vektorių funkcijų veikima tarp custom ir std vektorių
![](pics/compare.png)
![](pics/shrink_to_fit.png)
![](pics/resize.png)
![](pics/pop_back.png)
![](pics/capacity.png)

## Palyginau kiek laiko užima užpildyti skirtingų dydžių vektorius
![](pics/std_vector.png)
![](pics/custom_vector.png)

## Palyginau kiek kartu perskirstoma atmintis pildant 10000000 dydžio vektorius
![](pics/grow1.png)
![](pics/grow2.png)


## Palyginau trečiosios programos testų atlikimų greitį naudojant 100000 dydžio vektorius
![](pics/sparta_std.png)
![](pics/sparta_custom.png)
