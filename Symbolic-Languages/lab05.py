import lab05

def rozmowa():
    text.center('Rozmowa z: Mietek')
    text.left("Mietek: Witaj, mój ulubiony kolego!")
    text.right("Ja: Witaj, nieznajomy")
    text.right('Ja: Jak mogę ci pomóc tego pięknego dnia?')
    text.left('Mietek: Jeśli nie chcesz mojej zguby')
    text.left('Mietek: To gotowca daj mi, luby!')
    text.right('Ja: Nie')
    text.left('Mietek: To nie')

rozmowa()

print(fib.iterative(123))
print(fib.recursive(12))

def sqrt():
    language = input("Podaj język (PL lub EN): ")
    while language!="PL" and language!="EN":
        language = input("Język nieprawidłowy. Podaj ponownie: ")
    if language=="PL":
        from dictionary import pl as d
    else:
        from dictionary import en as d
    print(d.lang['hello'])
    try:
        number = int(input(d.lang['info']))
    except ValueError:
        print(d.lang['error'])
        print(d.lang['bye'])
        return
    import math
    root = math.sqrt(number)
    print(root)
    print(d.lang['bye'])

sqrt()

