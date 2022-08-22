import cv2
import os
import numpy as np

f = open('test.csv', 'r')
ls = f.readlines()[1:]

res = open('res.csv', 'w')
res.write('label\n')

out_size = 16

def is_square(approx):
    if (len(approx) != 4):
        return False

    p1 = approx[0][0]
    p2 = approx[2][0]
    p3 = approx[3][0]
    if abs(abs(p1[0] - p2[0]) - abs(p2[1] - p3[1])) > 5:
        return False

    return True

for fn in ls:
    fn = fn.strip()
    fn = "train_data/7.png" #fn.strip()
    print("Processing", fn)
    img = cv2.imread(fn)

    colors, counts = np.unique(np.concatenate(np.asarray(img), axis=0), axis=0, return_counts = True)
    for i in range(len(colors) - 1):
        print(colors[i], counts[i])
        img1 = cv2.inRange(img, colors[i], colors[i])
        img_erode = cv2.dilate(img1, np.ones((3, 3), np.uint8), cv2.BORDER_REFLECT, iterations=1)
        cv2.imshow("colored" + str(i), img_erode)
    
    cv2.waitKey(0)
    break

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, thresh = cv2.threshold(gray, 254, 255, cv2.THRESH_BINARY)
    img_erode1 = cv2.erode(thresh, np.ones((4, 4), np.uint8), cv2.BORDER_REFLECT, iterations=1)
    img_erode = cv2.dilate(img_erode1, np.ones((3, 3), np.uint8), cv2.BORDER_REFLECT, iterations=1)

    # Get contours
    contours, hierarchy = cv2.findContours(img_erode, cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)

    print("Found", len(contours), "contours")
    sqs = []

    output = img.copy()
    for idx, contour in enumerate(contours):
        if idx == len(contours) - 1:
            break
        (x, y, w, h) = cv2.boundingRect(contour)

        ## cv2.rectangle(output, (x, y), (x + w, y + h), (70, 0, 0), 1)
        approx = cv2.approxPolyDP(contour, 0.005*cv2.arcLength(contour, True), True)
        cv2.drawContours(gray, [contour], 0, (0,255,0), 3)

        x = max(x - 6, 0)
        y = max(y - 6, 0)

        #print("R", idx, x, y, w, h, cv2.contourArea(contour), hierarchy[0][idx])

        sq = img_erode[y:y + h + 12, x:x + w + 12]
        if (is_square(approx)):
            cv2.drawContours(output, [approx], 0, (0,255,0), 1)
            sqs.append((x, w, sq))
        else:
            cv2.drawContours(output, [approx], 0, (0,0,255), 1)
    cv2.imshow("img", img)
    cv2.imshow("Output", output)
    cv2.imshow("gray", gray)
    # cv2.imshow("thresh", thresh)
    # cv2.imshow("img_erode1", img_erode1)
    # cv2.imshow("img_erode", img_erode)
    # i = 0
    # for l in sqs:
        # i += 1
        # cv2.imshow(str(i), l[2])
    print("Found", len(sqs), "squares")
    if len(sqs) == 0:
        res.write("1")
    else:
        res.write(str(len(sqs)))
    res.write('\n')
    cv2.waitKey(0)
    break;

res.close()

