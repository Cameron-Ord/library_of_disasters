import pygame
import sys
pygame.init()
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Triangle Renderer")

white = (255,255,255)
red = (255,0,0)

triangle_vertices = [(400, 100), (200, 500), (600, 500)]

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
    screen.fill(white)
    pygame.draw.polygon(screen,red,triangle_vertices)
    pygame.display.flip()


