""" Test file to make sure my math is right """

def percent_to_rgb(pct):
    """ Converts a percent between 0 and 1 to a color on the color spectrum, with
    green being low, red being mid, and blue being high. Returns tuple of 
    (r, g, b) with each value being 0.0-1.0.

    Does so by lerping such that 0 is (1, 0, 0), 0.5 is (0, 1, 0), 1 is (0, 0, 1),
        0.25 is (0.5, 0.5, 0), 0.75 is (0, 0.5, 0.5), etc. """

    # Remember that percent is (val-min)/(max-min)

    if(pct <= 0.5):
        # Since 0.5 is R and 0.0 is G, the R amount should just be how close
        #   we are to 0.5; G should be the inverse of this, hence why G's value
        #   is 0.5 - pct
        red_pct = (pct-0.0)/(0.5-0.0)
        green_pct = (0.5-pct)/(0.5-0.0)
        return( green_pct, red_pct, 0 )
    else:
        # B should of course be however close we are to 1, but consider that 
        #   to be how close we are to 1 with 0.5 being as far away as possible
        # R here is 1.0 - pct for the same reason why G above is 0.5 - pct
        red_pct = (1.0-pct)/(1.0-0.5)
        blue_pct = (pct-0.5)/(1.0-0.5)
        return( 0, red_pct, blue_pct)



if __name__ == "__main__":
    steps = 8
    pct_per_step = 1.0 / steps
    for i in range(0, steps + 1):
        rgb = percent_to_rgb(pct_per_step * i)
        print("{} is ({}, {}, {})".format(pct_per_step * i, rgb[0], rgb[1], rgb[2]))