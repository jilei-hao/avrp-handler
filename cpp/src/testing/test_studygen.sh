#! /bin/bash

gen=/Users/jileihao/dev/avrspt-dev/avrp-handler/build/studygen/StudyGen
# gen=/Users/jileihao/dev/avrspt-dev/AVRSPT-StudyGen/build/StudyGen


# time $gen -i "/Users/jileihao/data/avrspt/tav48/ds/img4d_ds50.nii.gz" \
# -o "/Users/jileihao/data/studygen/output" \
# -s "/Users/jileihao/data/avrspt/tav48/ds/seg02_ds50.nii.gz" \
# -s_ref 2 \
# -s_tgt "1,3,4,5" \
# -s "/Users/jileihao/data/avrspt/tav48/ds/seg09_ds50.nii.gz" \
# -s_ref 9 \
# -s_tgt "6,7,8,9,10,11,12,13,14" \
# -lc "/Users/jileihao/dev/avrspt-dev/AVRSPT-StudyGen/testing/data/test_label_config.json" \
# -nt 14


time $gen -i "/Users/jileihao/dev/avrspt-dev/avrp-handler/build/work_dir/download/4.nii.gz" \
-o "/Users/jileihao/dev/avrspt-dev/avrp-handler/build/work_dir/upload" \
-s "/Users/jileihao/dev/avrspt-dev/avrp-handler/build/work_dir/download/5.nii.gz" \
-s_ref 2 \
-s_tgt "1,3,4,5" \
-s "/Users/jileihao/dev/avrspt-dev/avrp-handler/build/work_dir/download/6.nii.gz" \
-s_ref 9 \
-s_tgt "6,7,8,9,10,11,12,13,14" \
-lc "/Users/jileihao/dev/avrspt-dev/avrp-handler/build/work_dir/example_label_config.json" \
-nt 14
