import re

def main():
    data = "background: linear-gradient(90deg, rgba(208,27,80,1) 0%, rgba(108,78,250,1) 33%, rgba(200,53,242,1) 67%, rgba(252,55,170,1) 100%);"
    vals = re.findall(r'rgba\((\d+),(\d+),(\d+),\d+\) (\d+)', data)
    print("DEFINE_GRADIENT_PALETTE (__NAME__) {")
    for val in vals:   
        print("    %d, %s, %s, %s," % (int(val[3])*2.55, val[0], val[1], val[2]))
    print("};")


if __name__=="__main__":
    main()


