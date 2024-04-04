#include "game.h"

#include <iostream>

Game::Game() {
	window = nullptr;
	renderer = nullptr;
	ground = new Ground();
	background = new Texture();
	gameOverTexture = new Texture();
    pause = new Texture();
	bird = new Bird();
	score = new Score();
    flappy = new Texture();
    prepare = new Texture();
    pauseButton = new Texture();
    resumeButton = new Texture();
	isOver = false;
    stop = true;
    prepareGame = true;
}

Game::~Game() {
    for (Pipe* & pipe : pipes) {
        delete pipe;
        pipe = nullptr;
    }
    for (Texture* & button : buttons) {
        delete button;
        button = nullptr;
    }
    delete prepare;
    delete flappy;
    delete ground;
    delete background;
    delete bird;
    delete gameOverTexture;
    delete score;
    delete pause;
    delete pauseButton;
    delete resumeButton;
    ground = nullptr;
    background = nullptr;
    bird = nullptr;
    gameOverTexture = nullptr;
    score = nullptr;
    pause = nullptr;
    flappy = nullptr;
    prepare = nullptr;
    pauseButton = nullptr;
    resumeButton = nullptr;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

bool Game::initSDL() {
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Initialize SDL %s", SDL_GetError());
		success = false;
	}
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create window %s", SDL_GetError());
		success = false;
	}
	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Initialize SDL %s", SDL_GetError());
		success = false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create renderer %s", SDL_GetError());
		success = false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	return success;
}

bool Game::initGame() {
	background->loadTexture(renderer, "assets/image/background.png");
	bird->loadBird(renderer);
	ground->loadGround(renderer, "assets/image/land.png");
	gameOverTexture->loadTexture(renderer, "assets/image/gameOver.png");
	score->loadImage(renderer);

	for (int i = 0; i < 2; i++) {
	    Texture* button = new Texture();
		if (!button->loadTexture(renderer, ("assets/buttons/" + std::to_string(i) + ".png").c_str())) {
		    return false;
		}
		buttons.push_back(button);
	}

	flappy->loadTexture(renderer, "assets/image/flappy.png");
    pause->loadTexture(renderer, "assets/image/pauseTab.png");
    prepare->loadTexture(renderer, "assets/image/prepare.png");
    pauseButton->loadTexture(renderer, "assets/image/pauseButton.png");
    resumeButton->loadTexture(renderer, "assets/image/resumeButton.png");
    return true;
}

void Game::prepareScene() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void Game::presentScene() {
	SDL_RenderPresent(renderer);
}

void Game::renderGround() {
	if (!stop && !isOver) ground->updateGround();
	ground->renderGround(renderer);
}

void Game::spawnPipe() {
	Pipe* pipe = new Pipe();
	pipe->loadPipe(renderer);
	pipes.push_back(pipe);
}

void Game::managePipe() {
    if (!isOver) {
        for (Pipe* & pipe : pipes) {
            pipe->updatePipe();
        }
   
        if (pipes.empty() || pipes.back()->getTopPipePosition().x < SCREEN_WIDTH - 150) {
            spawnPipe();
        }
    }
	else {
	    for (Pipe* & pipe : pipes) {
	        pipe-> updateDeadPipe();
	    }
	}

    for (auto it = pipes.begin(); it != pipes.end();) {
        if ((*it)->isOffScreen()) {
            delete *it;
            it = pipes.erase(it);
        }
        else {
            ++it;
        }
    }
}



void Game::renderPipe() {
	for (Pipe* &pipe : pipes) {
	    pipe->renderPipe(renderer);
	}
}

void Game::checkCollision() {
	Position birdPos = bird->getPosition();
	//GROUND_HEIGHT = 140, PIPE_GAP = 162, PIPE_WIDTH = 65, PIPE_HEIGHT = 373;
	//BIRD_WIDTH = 34, BIRD_HEIGHT = 24;

	if(birdPos.y + 24 >= SCREEN_HEIGHT - 140) {
	    isOver = true;
		return;
	}

	for (Pipe* &pipe : pipes) {
	    Position topPipePos = pipe->getTopPipePosition();
		Position bottomPipePos = pipe->getTopPipePosition();

		if (birdPos.x + 34 >= topPipePos.x &&  birdPos.x <= topPipePos.x + 65 && birdPos.y <= 373 - topPipePos.y) {
		    isOver = true;
			return;
		}

		if (birdPos.x + 34 >= bottomPipePos.x && birdPos.x <= bottomPipePos.x + 65 && birdPos.y + 24 >= 373 - topPipePos.y + 162) {
		    isOver = true;
			return;
		}
	}

}


void Game::handleInput(SDL_Event& e, bool& quit) {
    int mouseX = 0, mouseY = 0;
    switch (e.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_SPACE) {
                switch (gameState) {
                    case MENU:
                        gameState = PREPARE;
                        break;
                    case PREPARE:
                        gameState = PLAY;
                        stop = false;
                        break;
                    case PLAY:
                        if (!isOver) bird->flap();
                        break;
                    case PAUSE:
                        gameState = PLAY;
                        stop = false;
                        break;
                    case GAME_OVER:
                        resetGame();
                        break;
                }
            }
            if (e.key.keysym.sym == SDLK_p) {
                switch (gameState) {
                    case PLAY:
                        gameState = PAUSE;
                        stop = true;
                        break;
                    case PAUSE:
                        gameState = PLAY;
                        stop = false;
                        break;
                }
            }
            if (e.key.keysym.sym == SDLK_r) {
                if (gameState == GAME_OVER) {
                    resetGame();
                }
            }
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                switch (gameState) {
                    case PREPARE:
                        gameState = MENU;
                        stop = true;
                        break;
                    case PLAY:
                    case PAUSE:
                    case GAME_OVER:
                        gameState = MENU;
                        stop = true;
                        break;
                    case MENU:
                        quit = true;
                        break;
                }
            }
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&mouseX, &mouseY);
                switch (gameState) {
                    case PAUSE:
                        if (mouseX >= SCREEN_WIDTH - 36 && mouseX <= SCREEN_WIDTH - 10 && mouseY >= 10 && mouseY <= 38) {
                            gameState = PLAY;
                            stop = false;
                        }
                        break;
                    case PLAY:
                        if (mouseX >= SCREEN_WIDTH - 36 && mouseX <= SCREEN_WIDTH - 10 && mouseY >= 10 && mouseY <= 38) {
                            gameState = PAUSE;
                            stop = true;
                        }
                        break;
                }
            }
    }
}

void Game::resetGame() {
    isOver = false;
    bird->resetBird();
    score->resetScore();
    for (Pipe* & pipe : pipes) {
        delete pipe;
        pipe = nullptr;
    }
    pipes.clear();
    gameState = PREPARE;
    stop = true;
}


void Game::updateGame() {
    background->renderTexture(renderer, 0, 0);
    switch (gameState) {
        case MENU:
            renderGround();
            flappy->renderTexture(renderer, SCREEN_WIDTH / 2 - 125, 100);
            break;
        case PREPARE:
            renderGround();
            bird->renderBird(renderer);
            prepare->renderTexture(renderer, 63, 180);
            break;
        case PAUSE:
            renderPipe();
            bird->renderBird(renderer);
            renderGround();
            resumeButton->renderTexture(renderer, SCREEN_WIDTH - 36 , 10);
            pause->renderTexture(renderer, 50, 232);
            score->renderSmallScore(renderer);
            break;
        case PLAY:
            renderPipe();
            checkCollision();
            if (!isOver) {
                bird->updateBird();
                score->incrementScore(pipes, bird->getPosition());
                score->checkBestScore();
            }
            else {
                gameState = GAME_OVER;
            }
        case GAME_OVER:  
            if (isOver) bird->updateDeadBird();
            managePipe();
            renderPipe();
            bird->renderBird(renderer);
            if (!isOver) {
                score->renderLargeScore(renderer);
                pauseButton->renderTexture(renderer, SCREEN_WIDTH - 36, 10);
            }
            renderGround();
            if (isOver) {
                gameOverTexture->renderTexture(renderer, 50, 150);
                score->renderSmallScore(renderer);
                score->renderMedal(renderer);
                score->saveBestScore();
            }
            break;
    }
}
