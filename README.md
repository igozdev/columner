# columner
Command-line applicaion for generating stratigraphic column templates

## Additional requirements
![stb_image_write.h](https://github.com/nothings/stb/blob/master/stb_image_write.h)

## Usage
`columner [x_resolution] [y_resolution] [left_margin] [top_margin] [num_of_major_ticks] [num_of_semimajor_ticks] [num_of_minor_ticks] [tick_stride] [num_of_verticals] [vertical_stride] [major_brightness] [semimajor_brightness] [minor_brightness] [vertical_brightness] [path]`

## Example
Output of `columner 200 320 30 30 5 1 4 10 6 3 5 8 10 240 250 255 200 "column.png"`: <br><br>
![example](https://github.com/igozdev/columner/blob/main/column.png)
