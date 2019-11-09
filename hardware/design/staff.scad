$fn = 64;

led_count = 4;


module LED()
{
    cylinder(d = 5.2, h= 6);
    translate([0,0,6])
    sphere(d = 5.2);
}

module BatteryBox()
{
    linear_extrude(30)
    difference()
    {
        hull()
        {
            for(i = [-1,1])
            translate([i*7,0])
            circle(d=8.5);
        }

        hull()
        {
            for(i = [-1,1])
            translate([i*7,0])
            circle(d=6.5);
        }
    }

    translate([0,0,-1])
    hull()
    {
        for(i = [-1,1])
        translate([i*7,0])
        cylinder(d=8.5,h=1);
    }
}

module EspBox()
{
    difference()
    {
        union()
        {
            cube([13, 25, 11]);
            cube([51, 25, 3]);
        }

        translate([1,1, 11-8])
        cube([12, 23, 7]);

        for (yr = [-1, 1])
        translate([1+25, 25/2 + yr * (21/2), 2])
        cube([50,2,2], center= true);
    }

    for(yr = [3, 20])
    translate([51, yr])
    cube([2,2,4]);
}

module CoreElectronics()
{
    translate([25/2,0])
    rotate(90)
    EspBox();

    translate([0, 1, -3.25])
    rotate([-90,0,0])
    BatteryBox();
}

module Supports()
{
    for(xr = [-1, 1])
    translate([xr * 15.5, -7, -55])
    cylinder(d = 8, h = 55);

    for(xr = [-1, 1])
    {
        hull()
        {
            translate([xr * 15.5, -7, -55])
            sphere(d=8);
            translate([xr * 12, -5, -65])
            sphere(d=8);
        }

        difference()
        {
            hull()
            {
                translate([xr * 12, -5, -65])
                sphere(d=8);
                translate([0, 0, -75])
                cylinder(d=10,h=5);
            }
            cylinder(d=3,h=1000, center=true);
        }
    }

}

module DrilledCrystal()
{
    difference()
    {
        //scale(30)
        import("crystal.stl");

        // Led holes
        for(i = [0:led_count])
        {
            rotate(i * 360/led_count)
            translate([20, 0])
            LED();
        }

    }

    // Electronics
    translate([0, -9, 1])
    rotate([-90,0,0])
    CoreElectronics();


    // Support
    Supports();
}


module ScrewCore()
{
    difference()
    {
        cylinder(d= 27, h = 68);
        cylinder(d= 3, h=3);

        translate([0,0, 24.5])
        cylinder(d= 24.5, h= 100);

        translate([0, 0, 3])
        cylinder(d= 18.2, h=30);
    }
}

module Gnarl()
{
    difference()
    {
        import("gnarl.stl");

        cylinder(d = 24.5, h= 1000, center = true);
    }

    translate([0, 0, -75])
    rotate([180,0,0])
    ScrewCore();
}

*DrilledCrystal();
intersection ()
{
    Gnarl();
    cube(2 * 75 + 3, center = true);
}
*difference ()
{
    Gnarl();
    cube(2 * 75 + 3, center = true);
}
