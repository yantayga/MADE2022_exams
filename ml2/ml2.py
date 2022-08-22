import cv2
import os
import numpy as np
import math

debug = 0

f = open('test.csv', 'r')
ls = f.readlines()[1:]

res = open('res.csv', 'w')
res.write('label\n')

# delta_size = 2 erode_size = 5 approx_coef = 0.02 RMSE= 0.007363574011458174
# delta_size = 3 erode_size = 5 approx_coef = 0.02 RMSE= 0.007333333333333333
# delta_size = 4 erode_size = 5 approx_coef = 0.02 RMSE= 0.007796010375684333 

# delta_size = 2 erode_size = 7 approx_coef = 0.02 RMSE= 0.0072724747430904756
# delta_size = 3 erode_size = 7 approx_coef = 0.02 RMSE= 0.006984108946585655
# delta_size = 4 erode_size = 7 approx_coef = 0.02 RMSE= 0.007423685817106695

# delta_size = 3 erode_size = 4 approx_coef = 0.02 RMSE= 0.008006941432976209
# delta_size = 3 erode_size = 5 approx_coef = 0.02 RMSE= 0.007333333333333333
# delta_size = 3 erode_size = 6 approx_coef = 0.02 RMSE= 0.0071102430025671804
# delta_size = 3 erode_size = 7 approx_coef = 0.02 RMSE= 0.006984108946585655
# delta_size = 3 erode_size = 8 approx_coef = 0.02 RMSE= 0.007333333333333333
# delta_size = 3 erode_size = 10 approx_coef = 0.02 RMSE= 0.007505553499465134

# delta_size = 3 erode_size = 7 approx_coef = 0.01  RMSE= 0.011761519176251569
# delta_size = 3 erode_size = 7 approx_coef = 0.015 RMSE= 0.007055336829505575
# delta_size = 3 erode_size = 7 approx_coef = 0.02  RMSE= 0.006984108946585655
# delta_size = 3 erode_size = 7 approx_coef = 0.035 RMSE= 0.006984108946585655
# delta_size = 3 erode_size = 7 approx_coef = 0.05  RMSE= 0.006984108946585655
# delta_size = 3 erode_size = 7 approx_coef = 0.075 RMSE= 0.006984108946585655
# delta_size = 3 erode_size = 7 approx_coef = 0.1   RMSE= 0.008819171036881969

# Main is
# delta_size = 3 erode_size = 7 approx_coef = 0.05  RMSE= 0.0069282032302755096

delta_size = 3
erode_size = 7
approx_coef = 0.051

def is_square(approx, need_roll):
    if (len(approx) > 4):
        return False

    if (len(approx) < 4):
        return True
    
    if need_roll:
        approx = np.roll(approx, 2)
    
    p1 = approx[0][0]
    p2 = approx[1][0]
    p3 = approx[2][0]
    p4 = approx[3][0]
    dx = abs(p1[0] - p4[0])
    dy = abs(p1[1] - p2[1])
    sx = abs(p1[0] - p2[0])
    sy = abs(p2[1] - p3[1])

    if dx > delta_size or dy > delta_size:
        return False

    if abs(sx - sy) > delta_size:
        return False

    return True

deltas = 0.0
j = 0
for line in ls:
    line = line.split(',')
    if len(line) > 1:
        predicted = int(line[1])
    else:
        predicted = '?'
    fn = line[0].strip()
    # if debug:
        # fn = "train_data/165.png"
    print("Processing", fn)
    img = cv2.imread(fn)

    if debug:
        output = img.copy()

    colors, counts = np.unique(np.concatenate(np.asarray(img), axis=0), axis=0, return_counts = True)
    if debug:
        sqs = []
    found = 0
    for i in range(len(colors) - 1):
        if debug:
            print("Checking color ", colors[i], ", n=", counts[i])

        img1 = cv2.inRange(img, colors[i], colors[i])
        img_erode = cv2.dilate(img1, np.ones((erode_size, erode_size), np.uint8), cv2.BORDER_REFLECT, iterations=1)
        if debug > 1:
            cv2.imshow("colored " + str(i), img_erode)
    
        # Get contours
        contours, hierarchy = cv2.findContours(img_erode, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        if debug:
            print("Found", len(contours), "contours on", i, "color")

        for idx, contour in enumerate(contours):
            if len(contours) > 1 and idx == len(contours) - 1:
                break
            convex = cv2.convexHull(contour)
            approx = cv2.approxPolyDP(convex, approx_coef*cv2.arcLength(contour, True), True)
            if debug:
                cv2.drawContours(output, [contour], 0, (255,0,0), 7)
                cv2.drawContours(output, [convex], 0, (127,127,127), 4)

            if debug:
                (x, y, w, h) = cv2.boundingRect(contour)
                x = max(x - erode_size, 0)
                y = max(y - erode_size, 0)
                #print("R", idx, x, y, w, h, cv2.contourArea(contour), hierarchy[0][idx])
                sq = img_erode[y:y + h + erode_size * 2, x:x + w + erode_size* 2]

            if (is_square(approx, len(contours) == 1)):
                found += 1
                if debug:
                    cv2.drawContours(output, [approx], 0, (0,255,0), 1)
                    sqs.append((x, w, sq))
            else:
                if debug:
                    cv2.drawContours(output, [approx], 0, (0,0,255), 3)
    if len(line) > 1:
        deltas += ( found - predicted ) ** 2
    j += 1
    print("Found", found, "of", predicted, "squares, RMSE=", math.sqrt(deltas)/j)

    res.write(str(found))
    res.write('\n')

    if debug:
        cv2.imshow("Output " + fn, output)
        if len(line) == 1 or abs(len(sqs) - predicted) > 0:
            if cv2.waitKey(0) == 27:
                break
        cv2.destroyAllWindows()
        # break

res.close()

print("# delta_size =",delta_size,"erode_size =",erode_size,"approx_coef =",approx_coef,"RMSE=",math.sqrt(deltas)/j)
