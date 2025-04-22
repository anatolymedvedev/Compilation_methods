Alternative = {
    "A1": "!B!",
    "B1": "T",
    "B2": "T+B",
    "T1": "M",
    "T2": "M*T",
    "M1": "a",
    "M2": "b",
    "M3": "(B)",
}
Alternative_idx = {
    "A1": "1",
    "B1": "2",
    "B2": "3",
    "T1": "4",
    "T2": "5",
    "M1": "6",
    "M2": "7",
    "M3": "8",
}
T = ["a", "b", "(", ")", "!", "+", "*"]
l1 = []
l2 = str("A")
res = str(input("Введите строку ="))
res_res = ""
n = len(res)
i = 0
state = "q"

while True:
    if state == "q":
        if l2[0] in T:
            if l2[0] == res[i]:
                # step 2
                l1.append(l2[0])
                l2 = l2[1:]
                i += 1
                if i == n:
                    if len(l2) == 0:
                        # step 3
                        state = "t"
                        continue
                    else:
                        # step 3'   #цепочка вся прочитана, но стек l2не пуст
                        state = "b"
                        continue
                else:
                    if len(l2) == 0:
                        # step 3'   #цепочка  прочитана не вся, а в дереве вывода уже нет вершин
                        state = "b"
                        continue
                    else:
                        continue
            else:
                # step 4
                state = "b"
                continue
        else:
            # step 1
            alt_l1 = l2[0] + "1"
            l1.append(alt_l1)
            l2 = l2.replace(alt_l1[0], Alternative.get(alt_l1), 1)
            continue
    elif state == "b":
        if l1[len(l1) - 1] in T:
            # step 5
            l2 = l1[len(l1) - 1] + l2
            l1 = l1[: len(l1) - 1]
            i -= 1
            continue
        else:
            alt_idx_l1 = l1[len(l1) - 1]
            new_alt_idx_l1 = alt_idx_l1[0] + chr(ord(alt_idx_l1[1]) + 1)
            if Alternative.get(new_alt_idx_l1) != None:  # есть еще другая альтернатива у l1[j+1]
                # step 6a
                l1 = l1[: len(l1) - 1]
                l1.append(new_alt_idx_l1)
                l2 = l2.replace(Alternative.get(alt_idx_l1), Alternative.get(new_alt_idx_l1), 1)
                state = "q"
                continue
            else:
                if (new_alt_idx_l1 == "A2") and (i == 0):
                    # step 6b
                    print("Ошибка")
                    break
                else:
                    # step 6v
                    l2 = l2.replace(Alternative.get(alt_idx_l1), alt_idx_l1[0], 1)
                    l1 = l1[: len(l1) - 1]
                    continue
    elif state == "t":
        for x in l1:
            if Alternative_idx.get(x) != None:
                res_res += " " + Alternative_idx.get(x)
        break

if res_res != "":
    res_res = res_res[1:]
    print(res_res)
else:
    print("Введенная строка не может быть выведена с помощью граматики")