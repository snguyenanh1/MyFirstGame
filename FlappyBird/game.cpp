#include "game.h"

#include <iostream>

Game::Game() {
	window = nullptr;
	renderer = nullptr;
	ground = new Ground();
	background = new Texture();
	gameOverTexture = new Texture();
    pause = new Texture();
	score = new Score();
    flappy = new Texture();
    prepare = new Texture();
    pauseButton = new Texture();
    resumeButton = new Texture();
    leftButton = new Texture();
    rightButton = new Texture();
    backgroundMusic = new Sound();
    gameOverMedal = new Sound();
    gameOverNoMedal = new Sound();
    bestScore = new Sound();
    jump = new Sound();
    dead = new Sound();
    backgroundMenu = new Sound();
    prepareMusic = new Sound();
    gameOverMusic = new Sound();
    click = new Sound();
	isOver = false;
    stop = true;
    birdType = 0;
    deadDuration = 165;
    deadTimer = 0;
    gameOverDurationNoMedal = 250;
    gameOverDuration = 380;
    gameOverTimer = 0;
    soundOn = true;
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
    for (Bird* & bird : birds) {
        delete bird;
        bird = nullptr;
    }
    for (Texture* & button : soundButton) {
        delete button;
        button = nullptr;
    }
    delete prepare;
    delete flappy;
    delete ground;
    delete background;
    delete gameOverTexture;
    delete score;
    delete pause;
    delete pauseButton;
    delete resumeButton;
    delete leftButton;
    delete rightButton;
    delete backgroundMusic;
    delete gameOverMedal;
    delete gameOverNoMedal;
    delete jump;
    delete dead;
    delete bestScore;
    delete backgroundMenu;
    delete prepareMusic;
    delete gameOverMusic;
    delete click;
    ground = nullptr;
    background = nullptr;
    gameOverTexture = nullptr;
    score = nullptr;
    pause = nullptr;
    flappy = nullptr;
    prepare = nullptr;
    pauseButton = nullptr;
    resumeButton = nullptr;
    backgroundMusic = nullptr;
    gameOverMedal = nullptr;
    gameOverNoMedal = nullptr;
    jump = nullptr;
    dead = nullptr;
    bestScore = nullptr;
    backgroundMusic = nullptr;
    prepareMusic = nullptr;
    gameOverMusic = nullptr;
    click = nullptr;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    Mix_Quit();
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
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Initialize SDL_mixer %s", Mix_GetError());
        success = false;
    }
	return success;
}

void Game::initGame() {
	background->loadTexture(renderer, "assets/image/background.png");
	ground->loadGround(renderer, "assets/image/land.png");
	gameOverTexture->loadTexture(renderer, "assets/image/gameOver.png");
	score->loadImage(renderer);
	for (int i = 0; i < 2; i++) {
	    Texture* button = new Texture();
		button->loadTexture(renderer, ("assets/buttons/" + std::to_string(i) + ".png").c_str()); 
		buttons.push_back(button);
	}
	flappy->loadTexture(renderer, "assets/image/flappy.png");
    pause->loadTexture(renderer, "assets/image/pauseTab.png");
    prepare->loadTexture(renderer, "assets/image/prepare.png");
    pauseButton->loadTexture(renderer, "assets/image/pauseButton.png");
    resumeButton->loadTexture(renderer, "assets/image/resumeButton.png");
    leftButton->loadTexture(renderer, "assets/image/left.png");
    rightButton->loadTexture(renderer, "assets/image/right.png");
    for (int idx = 0; idx < 3; idx++) {
        Bird* bird = new Bird();
        bird->loadBird(renderer, idx);
        birds.push_back(bird);
    }
    backgroundMusic->loadMusic("assets/sound/background.wav");
    gameOverMedal->loadSound("assets/sound/medal.wav");
    gameOverNoMedal->loadSound("assets/sound/noMedal.wav");
    jump->loadSound("assets/sound/jump.wav");
    dead->loadSound("assets/sound/dead.wav");
    bestScore->loadSound("assets/sound/record.wav");
    backgroundMenu->loadMusic("assets/sound/menu.wav");
    prepareMusic->loadMusic("assets/sound/prepare.wav");
    gameOverMusic->loadMusic("assets/sound/gameover.wav");
    click->loadSound("assets/sound/click.wav");
    Texture* buttonOn = new Texture();
    buttonOn->loadTexture(renderer, "assets/image/soundon.png");
    soundButton.push_back(buttonOn);
    Texture* buttonOff = new Texture();
    buttonOff->loadTexture(renderer, "assets/image/soundoff.png");
    soundButton.push_back(buttonOff);
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
	Position birdPos = birds[birdType]->getPosition();
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
            if(gameState != PLAY && soundOn) click->playSound();
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
                        birds[birdType]->flap();
                        if (soundOn) jump->playSound();
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
                    case PLAY:
                    case PAUSE:
                    case GAME_OVER:
                        resetGame();
                        break;
                    case MENU:
                        quit = true;
                        break;
                }
            }
            if (gameState == MENU && e.key.keysym.sym == SDLK_LEFT) {
                birdType = (birdType - 1 + 3) % 3;
            }
            if (gameState == MENU && e.key.keysym.sym == SDLK_RIGHT) {
                birdType = (birdType + 1) % 3;
            }
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&mouseX, &mouseY);
                if (gameState != PAUSE) {
                    if (mouseX >= 10 && mouseX <= 10 + 32 && mouseY >= 10 && mouseY <= 10 + 24) {
                        if (soundOn) {
                            soundOn = false;
                            Mix_PauseAudio(1);
                        }
                        else {
                            soundOn = true;
                            Mix_PauseAudio(0);
                        }
                    }
                }
                if (gameState == PAUSE && mouseX >= 105 && mouseX <= 105 + 32 && mouseY >= 277 && mouseY <= 277 + 24) {
                    if (soundOn) {
                        soundOn = false;
                        Mix_PauseAudio(1);
                    }
                    else {
                        soundOn = true;
                        Mix_PauseAudio(0);
                    }
                }
                if (gameState != PLAY && soundOn) click->playSound();
                switch (gameState) {
                    case MENU:
                        if (mouseX >= SCREEN_WIDTH / 2 - 17 - 5 - 13 && mouseX <= SCREEN_WIDTH / 2 - 17 - 5 && mouseY >= 255 && mouseY <= 255 + 24) {
                            birdType = (birdType - 1 + 3) % 3;
                        }
                        if (mouseX >= SCREEN_WIDTH / 2 + 17 + 5 && mouseX <= SCREEN_WIDTH / 2 + 17 + 5 + 13 && mouseY >= 255 && mouseY <= 255 + 24) {
                            birdType = (birdType + 1) % 3;
                        }
                        if (mouseX >= SCREEN_WIDTH / 2 - 50 && mouseX <= SCREEN_WIDTH / 2 + 50 && mouseY >= 300 && mouseY <= 350) {
                            gameState = PREPARE;
                        }
                        break;
                    case PREPARE:
                        gameState = PLAY;
                        stop = false;
                        break;
                    case PAUSE:
                        if (mouseX >= SCREEN_WIDTH - 36 && mouseX <= SCREEN_WIDTH - 10 && mouseY >= 10 && mouseY <= 38) {
                            gameState = PLAY;
                            stop = false;
                        }
                        if (mouseX >= SCREEN_WIDTH / 2 - 50 && mouseX <= SCREEN_WIDTH / 2 + 50 && mouseY >= 400 && mouseY <= 450) {
                            gameState = PLAY;
                            stop = false;
                        }
                        break;
                    case PLAY:
                        if (mouseX >= SCREEN_WIDTH - 36 && mouseX <= SCREEN_WIDTH - 10 && mouseY >= 10 && mouseY <= 38) {
                            gameState = PAUSE;
                            stop = true;
                        }
                        if (mouseX >= 10 && mouseX <= 10 + 32 && mouseY >= 10 && mouseY <= 10 + 24) {}
                        else  {
                            birds[birdType]->flap();
                            if (soundOn) jump->playSound();
                        }
                        break;
                    case GAME_OVER:
                        if (mouseX >= SCREEN_WIDTH / 2 - 50 && mouseX <= SCREEN_WIDTH / 2 + 50 && mouseY >= 400 && mouseY <= 450) {
                            resetGame();
                        }
                        break;
                }
            }
    }
}

void Game::resetGame() {
    isOver = false;
    score->resetScore();
    birds[birdType]->resetBird();
    for (Pipe* & pipe : pipes) {
        delete pipe;
        pipe = nullptr;
    }
    pipes.clear();
    gameState = MENU;
    stop = true;
    gameOverMedal->reset();
    gameOverNoMedal->reset();
    gameOverPosY = SCREEN_HEIGHT;
    dead->reset();
    bestScore->reset();
    backgroundMenu->reset();
    prepareMusic->reset();
    backgroundMusic->reset();
    backgroundMenu->reset();
    gameOverMedal->reset();
    prepareMusic->reset();
    gameOverNoMedal->reset();
    gameOverMusic->reset();
    deadTimer = 0;
    gameOverTimer = 0;
}

void Game::updateGame() {
    background->renderTexture(renderer, 0, 0);
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    switch (gameState) {
        case MENU:
            if(gameOverMedal->isPlaying()) gameOverMedal->stopMusic();
            if(gameOverNoMedal->isPlaying()) gameOverNoMedal->stopMusic();
            if (!backgroundMenu->isPlayedMusic() && soundOn) backgroundMenu->playMusic();
            renderGround();
            flappy->renderTexture(renderer, SCREEN_WIDTH / 2 - 125, 100);
            birds[birdType]->renderBird(renderer, true);
            leftButton->renderTexture(renderer, SCREEN_WIDTH / 2 - 17 - 5 - 13, 255);
            rightButton->renderTexture(renderer, SCREEN_WIDTH / 2 + 17 + 5, 255);
            if (mouseX >= SCREEN_WIDTH / 2 - 50 && mouseX <= SCREEN_WIDTH / 2 + 50 && mouseY >= 300 && mouseY <= 350)
                buttons[0]->renderTexture(renderer, SCREEN_WIDTH / 2 - 50, 300);
            else buttons[1]->renderTexture(renderer, SCREEN_WIDTH / 2 - 50, 300);
            soundOn ? soundButton[0]->renderTexture(renderer, 10, 10) : soundButton[1]->renderTexture(renderer, 10, 10);
            break;
        case PREPARE:
            if (!prepareMusic->isPlayedMusic() && soundOn) prepareMusic->playMusic();
            renderGround();
            birds[birdType]->renderBird(renderer);
            prepare->renderTexture(renderer, 63, 180);
            soundOn? soundButton[0]->renderTexture(renderer, 10, 10) : soundButton[1]->renderTexture(renderer, 10, 10);
            break;
        case PAUSE:
            renderPipe();
            birds[birdType]->renderBird(renderer);
            renderGround();
            resumeButton->renderTexture(renderer, SCREEN_WIDTH - 36, 10);
            pause->renderTexture(renderer, 50, 232);
            score->renderSmallScore(renderer);
            if (mouseX >= SCREEN_WIDTH / 2 - 50 && mouseX <= SCREEN_WIDTH / 2 + 50 && mouseY >= 400 && mouseY <= 450)
                buttons[0]->renderTexture(renderer, SCREEN_WIDTH / 2 - 50, 400);
            else buttons[1]->renderTexture(renderer, SCREEN_WIDTH / 2 - 50, 400);
            soundOn? soundButton[0]->renderTexture(renderer, 105, 277) : soundButton[1]->renderTexture(renderer, 105, 277);
            break;
        case PLAY:
            if (!backgroundMusic->isPlayedMusic() && soundOn) backgroundMusic->playMusic();
            checkCollision();
            if (!isOver) {
                birds[birdType]->updateBird();
                score->incrementScore(pipes, birds[birdType]->getPosition());
                if(score->checkBestScore() && !bestScore->isPlayedMusic()) bestScore->playSound();
                score->renderLargeScore(renderer);
                pauseButton->renderTexture(renderer, SCREEN_WIDTH - 36, 10);
            }
            if (isOver) gameState = AFTER_DEAD;
            managePipe();
            renderPipe();
            birds[birdType]->renderBird(renderer);
            renderGround();
            score->renderLargeScore(renderer);
            pauseButton->renderTexture(renderer, SCREEN_WIDTH - 36, 10);
            soundOn? soundButton[0]->renderTexture(renderer, 10, 10) : soundButton[1]->renderTexture(renderer, 10, 10);
            break;
        case AFTER_DEAD:
            backgroundMusic->stopMusic();
            if (!dead->isPlayedMusic() && soundOn) dead->playSound();
            birds[birdType]->updateDeadBird();
            managePipe();
            renderPipe();
            birds[birdType]->renderBird(renderer);
            renderGround();
            soundOn? soundButton[0]->renderTexture(renderer, 10, 10) : soundButton[1]->renderTexture(renderer, 10, 10);
            if (deadTimer < deadDuration) {
                deadTimer++;
            }
            else gameState = GAME_OVER;
            break;
        case GAME_OVER:
            birds[birdType]->renderBird(renderer);
            renderGround();
            bool finished = updateGameOver();
            gameOverTexture->renderTexture(renderer, 50, gameOverPosY);
            soundOn? soundButton[0]->renderTexture(renderer, 10, 10) : soundButton[1]->renderTexture(renderer, 10, 10);
            if (finished) {
                score->renderSmallScore(renderer);
                if (score->renderMedal(renderer)) {
                    if (!gameOverMedal->isPlayedMusic() && soundOn) gameOverMedal->playSound();
                    if (gameOverTimer < gameOverDuration) gameOverTimer++;
                    else {
                        if (!gameOverMusic->isPlayedMusic() && soundOn) gameOverMusic->playMusic();
                    }
                }
                else {
                    if (!gameOverNoMedal->isPlayedMusic() && soundOn) gameOverNoMedal->playSound();
                    if (gameOverTimer < gameOverDurationNoMedal) gameOverTimer++;
                    else {
                        if (!gameOverMusic->isPlayedMusic() && soundOn) gameOverMusic->playMusic();
                    }
                }
                score->saveBestScore();
                if (mouseX >= SCREEN_WIDTH / 2 - 50 && mouseX <= SCREEN_WIDTH / 2 + 50 && mouseY >= 400 && mouseY <= 450)
                    buttons[0]->renderTexture(renderer, SCREEN_WIDTH / 2 - 50, 400);
                else buttons[1]->renderTexture(renderer, SCREEN_WIDTH / 2 - 50, 400);
            }
            break;
    }
}

bool Game::updateGameOver() {
    if (gameOverPosY > 150) {
        gameOverPosY -= 10;
    }
    if (gameOverPosY < 150) gameOverPosY = 150;
    return gameOverPosY <= 150;
}