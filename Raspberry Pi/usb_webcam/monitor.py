import sys
import time
import pygame
import pygame.camera
import RPi.GPIO as GPIO

camera_res = (320, 240)
window_size = (640, 480)
red_pin = 18
green_pin = 23

pygame.init()
pygame.camera.init()

# initialize GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(red_pin, GPIO.OUT)
GPIO.setup(green_pin, GPIO.OUT)

screen = pygame.display.set_mode(window_size, 0)

#find, open and start low-res camera
cam_list = pygame.camera.list_cameras()
webcam = pygame.camera.Camera(cam_list[0], camera_res)
webcam.start()
old_image = False


def check_for_movement(old_image, new_image):
    global c
    diff_image = pygame.PixelArray(new_image).compare(pygame.PixelArray(old_image), distance=0.5, weights=(0.299, 0.587, 0.114))
    
    ys = range(0, camera_res[1] / 20)
    for x in range(0, camera_res[0] / 20):
        for y in ys:
            if diff_image[x*20, y*20] > 0:
                return True
    return False

def led_red():
    GPIO.output(red_pin, True)        
    GPIO.output(green_pin, False)  
    
def led_green():
    GPIO.output(red_pin, False)        
    GPIO.output(green_pin, True)  

count = 0
led_green()
while True:
    count = count + 1
    new_image = webcam.get_image()
    # First time round loop set old_image
    if not old_image:
        old_image = new_image
    scaled_image = pygame.transform.scale(new_image, window_size)
    # Pnly check one frame in 10
    if (count % 10) == 0 :
        if check_for_movement(old_image, new_image):
            led_red()
        count = 0
    old_image = new_image
    screen.blit(scaled_image, (0, 0))
    pygame.display.update()
    
    # check for events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            webcam.stop()
            pygame.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN:
            print(event.key)
            if event.key ==  32:  # Space
                led_green()
    #time.sleep(1.0)