from fpdf import FPDF
from PIL import Image

# List of image file paths (replace with the actual paths where you saved the images)
image_files = [
    "lab1_image1.png",
    "lab1_image2.png",
    "lab1_image3.png",
    "lab1_image4.png",
    "shell_script.png"
]

pdf = FPDF()
pdf.set_auto_page_break(0)

for image_file in image_files:
    cover = Image.open(image_file)
    width, height = cover.size
    width, height = float(width * 0.264583), float(height * 0.264583)  # convert px to mm
    pdf.add_page()
    pdf.image(image_file, 0, 0, width, height)

pdf.output("terminal_lab1_output.pdf")
