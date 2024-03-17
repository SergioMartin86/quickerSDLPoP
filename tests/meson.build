nomalloc = environment({'MALLOC_PERTURB_': '0'})

bash = find_program('bash')
testCommands = ['run_test.sh', SDLPoPTester.path(), quickerSDLPoPTester.path() ]
testTimeout = 30

# Tests to run
testSet = [ 
  'lvl01.anyPercent.test',
  'lvl01.pacifist.test',
  'lvl01.100percent.test',
  'lvl02.anyPercent.test',
  'lvl04.anyPercent.test',
  'lvl05.anyPercent.test',
  'lvl06.anyPercent.test',
  'lvl07.anyPercent.test',
  'lvl08.anyPercent.test',
  'lvl09.anyPercent.test',
  'lvl10.anyPercent.test',
  'lvl11.anyPercent.test',
  'lvl12.anyPercent.test',
  'lvl13.anyPercent.test',
  'lvl14.anyPercent.test',
  'lvl15.potion0.test',
]

# Adding tests to the suite
foreach testFile : testSet
  testSuite = testFile.split('.')[0]
  testName = testFile.split('.')[1]
  test(testName,
       bash,
       workdir : meson.current_source_dir(),
       timeout: testTimeout,
       args : [ testCommands, testFile, '--cycleType', 'Full'],
       suite : [ testSuite ])
endforeach