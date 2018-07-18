

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
        unitTypes[i].setFillColor( sf::Color::White );
        unitTypes[i].setPosition( 10.f, 110*(i+1) );
        //unitTypes[i].setRotation(180);
    }
    // texts with units categories
    unitTypes[HERO_UNITS].setString( "HERO UNITS" );
    unitTypes[MELEE_UNITS].setString( "MELEE UNITS" );
    unitTypes[RANGE_UNITS].setString( "RANGE UNITS" );
    unitTypes[ELITE_UNITS].setString( "ELITE UNITS" );
    unitTypes[SIEGE_UNITS].setString( "SIEGE UNITS" );
    unitTypes[MONSTERS].setString( "MONSTERS" );

    // unitsToChooseFromDB portraits and teams:
    for( auto& i : allNodUnitsDB ) {
        i.getPortrait().setScale(0.7f, 0.7f);
        i.setTeam( SECOND_ARMY );
    }

    for( auto& i : allGniUnitsDB ) {
        i.getPortrait().setScale(0.7f, 0.7f);
        i.setTeam( FIRST_ARMY );
    }

    for( int i=0; i<amountOfNodUnits; ++i ) {
        nodUnitsToChooseTs[i].loadFromFile( nodUnitsPaths[i] );
        nodUnitsToChooseSs[i].setTexture( nodUnitsToChooseTs[i] );
        nodUnitsToChooseSs[i].setScale( 0.5f, 0.5f );
    }

    for( int i=0; i<amountOfGniUnits; ++i ) {
        gniUnitsToChooseTs[i].loadFromFile( gniUnitsPaths[i] );
        gniUnitsToChooseSs[i].setTexture( gniUnitsToChooseTs[i] );
        gniUnitsToChooseSs[i].setScale( 0.5f, 0.5f );
    }

    allNodUnitsDB = {
                           Unit( nodUnitsToChooseSs[ attack_bike ],
                                 (char*)"Attack bike",
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ militant ],
                                 const_cast<char*>("Militant"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ avatar ],
                                 const_cast<char*>("Avatar"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ carryall ],
                                 const_cast<char*>("Carryall"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ commando_slut ],
                                 const_cast<char*>("Commando"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ fanatic ],
                                 const_cast<char*>("Fanatic"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ flame_tank ],
                                 const_cast<char*>("Flame tank"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ black_hand ],
                                 const_cast<char*>("Black hand"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ shadow ],
                                 const_cast<char*>("Shadow"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ scorp ],
                                 const_cast<char*>("Scorpion tank"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ saboteur ],
                                 const_cast<char*>("Saboteur"),
                                 100,
                                 10.f,
                                 1),

                           Unit( nodUnitsToChooseSs[ rocket ],
                                 const_cast<char*>("Rocket soldier"),
                                 100,
                                 10.f,
                                 1)

                   };

    allGniUnitsDB = {
            Unit( gniUnitsToChooseSs[ rifle ],
                  const_cast<char*>("Rifle trooper"),
                  100,
                  10.f,
                  1),

            Unit( gniUnitsToChooseSs[ missile ],
                  const_cast<char*>("Missile trooper"),
                  100,
                  10.f,
                  1),

            Unit( gniUnitsToChooseSs[ sniper ],
                  const_cast<char*>("Snoipeh"),
                  100,
                  10.f,
                  1),

            Unit( gniUnitsToChooseSs[ grenade ],
                  const_cast<char*>("Grenadier"),
                  100,
                  10.f,
                  1),

            Unit( gniUnitsToChooseSs[ mamooth ],
                  const_cast<char*>("Mammoth tank"),
                  100,
                  10.f,
                  1),

            Unit( gniUnitsToChooseSs[ colos ],
                  const_cast<char*>("Colos"),
                  100,
                  10.f,
                  1),

            Unit( gniUnitsToChooseSs[ commando ],
                  const_cast<char*>("Commando"),
                  100,
                  10.f,
                  1),

            Unit( gniUnitsToChooseSs[ bwp ],
                  const_cast<char*>("BWP"),
                  100,
                  10.f,
                  1),

            Unit( gniUnitsToChooseSs[ juggernaut ],
                  const_cast<char*>("Juggernaut"),
                  100,
                  10.f,
                  1),

    };
    nodUnitsDescriptions[attack_bike] = "Dank and fast bike";
    nodUnitsDescriptions[militant] = "Primary trooper";
    nodUnitsDescriptions[avatar] = "Advanced powerful mech";
    nodUnitsDescriptions[carryall] = "Armored air transporter";
    nodUnitsDescriptions[commando_slut] = "Dangerous girl";
    nodUnitsDescriptions[fanatic] = "Beliver";
    nodUnitsDescriptions[flame_tank] = "Like tank with fire";
    nodUnitsDescriptions[black_hand] = "Heavy troops with flamethrowers";
    nodUnitsDescriptions[shadow] = "Highly trained black\n"
                                    "ops unit";
    nodUnitsDescriptions[scorp] = "Primary battle tank";
    nodUnitsDescriptions[saboteur] = "Commando unit with\n"
                                     "setchel charges guy";
    nodUnitsDescriptions[rocket] = "anti tank infantry";

    gniUnitsDescriptions[rifle] = "Primary trooper";
    gniUnitsDescriptions[missile] = "Missiles guy";
    gniUnitsDescriptions[sniper] = "Dank snoipeh";
    gniUnitsDescriptions[grenade] = "Grenadier after advanved training";
    gniUnitsDescriptions[mamooth] = "This tank can wreck you\n"
                                    "up boyyy";
    gniUnitsDescriptions[colos] = "Heaviest artillery we have";
    gniUnitsDescriptions[commando] = "Special ops unit";
    gniUnitsDescriptions[bwp] = "Infantry transporter with HMG";
    gniUnitsDescriptions[juggernaut] = "Jagger jagger lalalala\n";

    // ###################################### NOD UNITS ######################################
    for( auto& x : allNodUnitsDB )
    {
        x.getPortrait().setOrigin( unitWidth/2, unitHeight/2 );
        x.getPortrait().setScale( 0.6f, 0.6f );
    }

    for( auto& x : allGniUnitsDB )
    {
        x.getPortrait().setOrigin( unitWidth/2, unitHeight/2 );
        x.getPortrait().setScale( 0.6f, 0.6f );
    }

    int xAligningIter = 0;
    // HERO UNITS
    for( int i=0; i<2; ++i )
    {
        nodUnitsToChooseSs[i].setPosition( 20.f+(unitWidth*i), 150 );
        ++xAligningIter;
    }
    xAligningIter = 0;
    // MELEE UNITS
    for( int i=2; i<6; ++i )
    {
        nodUnitsToChooseSs[i].setPosition( 20.f+(unitWidth*xAligningIter), 260 );
        ++xAligningIter;
    }
    xAligningIter = 0;
    // RANGE UNITS
    for( int i=6; i<8; ++i )
    {
        nodUnitsToChooseSs[i].setPosition( 20.f+(unitWidth*xAligningIter), 360 );
        ++xAligningIter;
    }
    xAligningIter = 0;
    // ELITE UNITS
    for( int i=8; i<10; ++i )
    {
        nodUnitsToChooseSs[i].setPosition( 20.f+(unitWidth*xAligningIter), 460 );
        ++xAligningIter;
    }
    xAligningIter = 0;
    // SIEGE UNITS

        nodUnitsToChooseSs[10].setPosition( 20.f+(unitWidth*xAligningIter), 580 );
        ++xAligningIter;

    xAligningIter = 0;
    // MONSTERS

        nodUnitsToChooseSs[11].setPosition( 20.f+(unitWidth*xAligningIter), 690 );

    for( auto& x : allNodUnitsDB )
    {
        x.getPortrait().setOrigin( unitWidth/2, unitHeight/2 );
        x.getPortrait().setScale( 0.6f, 0.6f );
    }
    //###################################### GNI UNITS ######################################
    xAligningIter = 0;
    // HERO UNITS
    for( int i=0; i<2; ++i )
    {
        gniUnitsToChooseSs[i].setPosition( 20.f+(unitWidth*xAligningIter), 150 );
        ++xAligningIter;
    }

    // MELEE UNITS
    xAligningIter = 0;
    for( int i=2; i<4; ++i ) {
        gniUnitsToChooseSs[i].setPosition(20.f + (unitWidth * xAligningIter), 260);
        ++xAligningIter;
    }
    // RANGE UNITS

    gniUnitsToChooseSs[4].setPosition( 20.f, 360 );
    // ELITE UNITS

    gniUnitsToChooseSs[5].setPosition( 20.f, 460 );
    // SIEGE UNITS

    gniUnitsToChooseSs[6].setPosition( 20.f, 580 );
    // MONSTERS

    gniUnitsToChooseSs[7].setPosition( 20.f, 690 );
    gniUnitsToChooseSs[8].setPosition( 20.f+unitWidth, 690 );







    // main texture with whole left menu of units to choose from

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
    // max 30 width
    //TODO function to insert \n after every 30 chars would b good
    // idea



    descriptionOfUnit.setPosition( 40.f, 170.f );
    unitDescriptionT.draw( descriptionOfUnit );
    unitDescriptionS.setPosition( windowWidth-descMenuWidth-5.f, 150.f );
    portraitOfUnitToDescribe.setTexture( nodUnitsToChooseTs[0] );
    portraitOfUnitToDescribe.setOrigin( nodUnitsToChooseTs[0].getSize().x/2,
                                        nodUnitsToChooseTs[0].getSize().y/2);
    portraitOfUnitToDescribe.setPosition( descMenuWidth/2, 100.f );
    unitDescriptionT.draw( portraitOfUnitToDescribe );
    unitDescriptionT.display();

    // portrait of unit to descript to


    //####################################################
    // END OF UNIT DESCRIPTION
    //####################################################

    //####################################################
    // BEGIN OF PLAYERS PORTRAITS
    //####################################################
    playerPortraitTs.first.loadFromFile( playerPortraitPaths[0] );
    playerPortraitTs.second.loadFromFile( playerPortraitPaths[1] );

    playerPortraitSs.first.setTexture( playerPortraitTs.first );
    playerPortraitSs.second.setTexture( playerPortraitTs.second );

    playerPortraitSs.first.setOrigin( racePortraitWidth/2, racePortraitWidth/2 );
    playerPortraitSs.second.setOrigin( racePortraitWidth/2, racePortraitWidth/2 );

    playerPortraitSs.first.setPosition( 270.f, racePortraitHeight/2 );
    playerPortraitSs.second.setPosition( windowWidth-270.f, racePortraitHeight/2 );
    //####################################################
    // END OF PLAYER PORTRAITS
    //####################################################

    //####################################################
    // SETTING TEAMS OF UNITS
    //####################################################


}