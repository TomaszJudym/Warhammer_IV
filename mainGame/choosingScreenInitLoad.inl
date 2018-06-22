

void ChoosingScreen::initLoad()
{
    // gonna use i multiple times
    int i;
    choosingScreenFont.loadFromFile( "font/Consolas.ttf" );


    //####################################################
    // LEFT MENU OF UNITS TO CHOOSE FROM
    //####################################################
    for( i=0; i<amountOfUnitTypes; ++i )
    {
        unitTypes[i].setFont( choosingScreenFont );
        unitTypes[i].setCharacterSize(16);
        unitTypes[i].setFillColor( sf::Color::Black );
        unitTypes[i].setPosition( 10.f, 128*(i+1) );
        //unitTypes[i].setRotation(180);
    }
    // texts with units categories
    unitTypes[HERO_UNITS].setString( "HERO UNITS" );
    unitTypes[MELEE_UNITS].setString( "MELEE UNITS" );
    unitTypes[RANGE_UNITS].setString( "RANGE UNITS" );
    unitTypes[ELITE_UNITS].setString( "ELITE UNITS" );
    unitTypes[SIEGE_UNITS].setString( "SIEGE UNITS" );
    unitTypes[MONSTERS].setString( "MONSTERS" );


    // main texture with whole left menu of units to choose from
    unitsToChooseFromRT.create( (unsigned int)backOfUToChooseSizeX, (unsigned int)windowHeight );
    unitsToChooseFromRT.clear( sf::Color::Cyan );
    // setting text objects
    for( i=0; i<amountOfUnitTypes; ++i )
    {
        unitsToChooseFromRT.draw( unitTypes[i] );
    }
    // sprite to display and manipulate menu with unit categories
    // to choose from
    unitsToChooseFromS.setTexture( unitsToChooseFromRT.getTexture() );
    unitsToChooseFromS.setPosition( 5.f, 200.f );
    unitsToChooseFromS.setTextureRect( sf::IntRect( 0, chooseScreenDeltaY, backOfUToChooseSizeX, backOfUToChooseSizeY  ) );
    // lots off magic numbers here
    // TODO refactor to make possible different
    // TODO units amounts in different types



    // unit portraits for left menu of units to choose from
    // hero untis
    for( i=0; i<amountOfNodUnits; ++i )
    {
        nodUnitsToChooseTs[i].loadFromFile( nodUnitsPaths[i] );
        nodUnitsToChooseSs[i].setTexture( nodUnitsToChooseTs[i] );
        nodUnitsToChooseSs[i].setScale( 0.5f, 0.5f );

    }
    // melee units
    int xAligningIter=0;
    for( i = 0; i<3; ++i )
    {
        nodUnitsToChooseSs[i].setPosition( 2.f+70.f*i, leftMenuItemsYoffset );
        unitsToChooseFromRT.draw( nodUnitsToChooseSs[i] );
    }
    // range units
    for( int i=3; i<5; ++i )
    {
        nodUnitsToChooseSs[i].setPosition( 2.f+70.f*xAligningIter, (leftMenuItemsYoffset*2)-30.f );
        unitsToChooseFromRT.draw( nodUnitsToChooseSs[i] );
        ++xAligningIter;
    }
    // elite units
    xAligningIter=0;
    for( int i=5; i<8; ++i )
    {
        nodUnitsToChooseSs[i].setPosition( 2.f+70.f*xAligningIter, (leftMenuItemsYoffset*3)-60.f );
        unitsToChooseFromRT.draw( nodUnitsToChooseSs[i] );
        ++xAligningIter;
    }
    //siege untis
    xAligningIter=0;
    for( int i=8; i<11; ++i )
    {
        nodUnitsToChooseSs[i].setPosition( 2.f+70.f*xAligningIter, (leftMenuItemsYoffset*4)-90.f );
        unitsToChooseFromRT.draw( nodUnitsToChooseSs[i] );
        ++xAligningIter;
    }
    //monsters
    // TODO for, for (hueh) future expansions
    xAligningIter=0;
    for( int i=11; i<=11; ++i )
    {
        nodUnitsToChooseSs[i].setPosition( 2.f+70.f*xAligningIter, (leftMenuItemsYoffset*5)-120.f );
        unitsToChooseFromRT.draw( nodUnitsToChooseSs[i] );
        ++xAligningIter;
    }
    // without display(), texture holds and shows content
    // flipped horizontally
    unitsToChooseFromRT.display();
    //####################################################
    // END OF LEFT UNITS TO CHOOSE MENU
    //####################################################

    //####################################################
    // BEGIN OF UNITS ALREADY CHOSEN
    //####################################################
    // background
    unitsChosenT.loadFromFile( "img/choosingMenu/unitsChoosedBg.png" );
    unitsChosenS.setTexture( unitsChosenT );
    unitsChosenS.setOrigin( backUChosenSizeX/2, backUChosenSizeY/2 );
    unitsChosenS.setPosition( windowWidth/2, windowHeight/2 );

    //points for easier placing chosen units in iterations
    for( auto& x : pointsOnMiddleTable )
    {
        x.setSize( sf::Vector2f(5.f, 5.f) );
        x.setFillColor( sf::Color::Red );
        x.setOrigin( 2.f, 2.5 );
    }

    sf::Vector2f unitsChosenLeftStlCorner( unitsChosenS.getPosition().x-backUChosenSizeX/2,
                                            unitsChosenS.getPosition().y-backUChosenSizeY/2);

     short pointsIter=0;
                            // number of columns + 1
    short deltaXofPoints = (short)backUChosenSizeX/4;
                            // number of rows + 1
    short deltaYofPoints = (short)backUChosenSizeY/7;

    xAligningIter=deltaXofPoints;
    int yAligningIter=deltaYofPoints;
    for( i=0; i<6; ++i )
    {
        for( int j=0; j<3; ++j )
        {
            pointsOnMiddleTable[pointsIter++].setPosition(
                    unitsChosenLeftStlCorner.x+xAligningIter,
                    unitsChosenLeftStlCorner.y+yAligningIter);
                    xAligningIter += deltaXofPoints;
        }
        xAligningIter = deltaXofPoints;
        yAligningIter += deltaYofPoints;
    }

    //####################################################
    // END OF UNITS ALREADY CHOSEN
    //####################################################

    //####################################################
    // BEGIN OF UNIT DESCRIPTION
    //####################################################
    unitDescriptionT.create( descMenuWidth ,backOfUToChooseSizeY );
    unitDescriptionS.setTexture( unitDescriptionT.getTexture() );
    unitDescriptionT.clear( sf::Color::Cyan );
    unitDescriptionT.draw( unitDescriptionS );
    descriptionOfUnit.setFont( choosingScreenFont );
    descriptionOfUnit.setCharacterSize( 10 );
    descriptionOfUnit.setFillColor( sf::Color::Black );
    descriptionOfUnit.setString( "Init desc\nMeans no desc" );
    descriptionOfUnit.setPosition( 40.f, 100.f );
    unitDescriptionT.draw( descriptionOfUnit );
    unitDescriptionT.display();
    unitDescriptionS.setPosition( windowWidth-descMenuWidth-5.f, 150.f );



    //####################################################
    // END OF UNIT DESCRIPTION
    //####################################################
}