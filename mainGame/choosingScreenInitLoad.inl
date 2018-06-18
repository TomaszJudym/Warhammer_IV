

void ChoosingScreen::initLoad()
{
    choosingScreenFont.loadFromFile( "font/Consolas.ttf" );

    // SIZE OF MAIN DIVS
    float tmpSize = 30.f;
    backUToChoose.setSize( sf::Vector2f( backOfUToChooseSizeX, backOfUToChooseSizeY )  );
    backUChosen.setSize( sf::Vector2f( backDescOfUnitsSizeX, backUChosenSizeY ));
    backDescOfUnits.setSize( sf::Vector2f( backUChosenSizeX, backDescOfUnitsSizeY ) );

    // ORIGIN OF MAIN DIVS
    backUToChoose.setOrigin( backOfUToChooseSizeX/2, backOfUToChooseSizeY /2 );
    backUChosen.setOrigin( backUChosenSizeX/2, backUChosenSizeY/2 );
    backDescOfUnits.setOrigin( backDescOfUnitsSizeX/2, backDescOfUnitsSizeY/2 );

    // COLORS OF MAIN DIVS
    backUToChoose.setFillColor( sf::Color::Yellow );
    backUChosen.setFillColor( sf::Color::Yellow );
    backDescOfUnits.setFillColor( sf::Color::Yellow );

    backUToChoose.setPosition( (windowWidth/3)-180.f, (windowHeight/2)+100.f );
    backUChosen.setPosition( ((windowWidth/3)*2)-195.f, (windowHeight/2)+100.f );
    backDescOfUnits.setPosition( ((windowWidth/3)*3)-130.f, (windowHeight/2)+100.f );
}