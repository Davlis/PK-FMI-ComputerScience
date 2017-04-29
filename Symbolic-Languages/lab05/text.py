# mode: -1 - left, 0 - middle, 1 - right

def initText(text, lineSize):
    charLeft = len(text)
    rows = charLeft // lineSize
    notFullRow = (charLeft % lineSize != 0)
    if notFullRow:
        rows += 1
    return (charLeft, rows)

def initRow(text, lineSize, charLeft, i, mode):
    start = i * lineSize
    if charLeft >= lineSize:
        end = (i + 1) * lineSize;
    else:
        end = i * lineSize + charLeft;
    spacesLeft = (lineSize - charLeft)
    if mode == -1 or spacesLeft <= 0:
        out = text[start:end]
    elif mode == 0:
        out = ' ' * (spacesLeft // 2)
        spacesLeft -= (spacesLeft // 2)
        out += text[start:end] + (' ' * spacesLeft)
    else:
        out = (' ' * spacesLeft) + text[start:end]
    return out

def left(text, lineSize=120):
    charLeft, rows = initText(text, lineSize)
    for i in range(rows):
        print(initRow(text, lineSize, charLeft, i, -1))
        charLeft -= lineSize

def right(text, lineSize=120):
    charLeft, rows = initText(text, lineSize)
    for i in range(rows):
        print(initRow(text, lineSize, charLeft, i, 1))
        charLeft -= lineSize

def center(text, lineSize=120):
    charLeft, rows = initText(text, lineSize)
    for i in range(rows):
        print(initRow(text, lineSize, charLeft, i, 0))
        charLeft -= lineSize

if __name__ == "__main__":
    print('Moduł "text" definiuje funkcje center, left i right i służy do:')
    left('Wypisania tekstu wyrównanego do lewej,')
    right('do prawej,')
    center('lub wycentrowanego.')
