import cv2
from glob import glob
import numpy as np

image_files = sorted(list(glob('./asset/*.png')))

for image_file in image_files:
    image = cv2.imread(image_file)
    # convert 16-bit image to 8-bit image
    float_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB).astype('float32') / 255.0
    R, G, B = cv2.split(float_image)
    R: np.ndarray = np.clip(np.uint64(np.floor(R * 32)), 0, 31)
    G: np.ndarray = np.clip(np.uint64(np.floor(G * 64)), 0, 63)
    B: np.ndarray = np.clip(np.uint64(np.floor(B * 32)), 0, 31)
    converted_data = (R << np.uint64(11) | G << np.uint64(5) | B).flatten()
    # print as C array
    print(f"{image_file} shape: {converted_data.shape}")
    for item in converted_data:
        print(f"{hex(item)},", end='')
    print("\n")